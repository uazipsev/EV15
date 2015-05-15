void calculateSensors() {


  //calculate the selections of each side (narrow down to a single value per side intelligently)

  if (frontS == 999)                                  // if the value is not initialized
    frontS = avgF(IRLF, IRSFL, IRSFR);                  //run averaging system to get ranged data
  else                                                //else
  frontS = selectFront(IRLF, IRSFL, IRSFR, frontS);   //update the system via smarter algorithm

  if (backS == 999)                                       // if the value is not initialized
    backS = avgB(IRLB, IRMB, IRSBL, IRSBR);                 //run averaging system to get ranged data
  else                                                    //else
  backS =  selectBack(IRLB, IRMB, IRSBL, IRSBR, backS);   //update the system via smarter algorithm

  if (leftS == 999)                              //if the value is not initialized
    leftS = avgS(IRLL, IRML);                      //run averaging system to get ranged data
  else                                           //else
  leftS =   selectSide(IRLL, IRML, leftS);       //update the system via smarter algorithm

  if (rightS == 999)                               // if the value is not initialized
    rightS = avgS(IRLR, IRMR);                       //run averaging system to get ranged data
  else                                             //else
  rightS =  selectSide(IRLR, IRMR, rightS);        //update the system via smarter algorithm

}

int validRead(int signal, int average) {
  int signalDifference = signal - average;
  return average + (signalDifference * 0.98);//.85 //0.50
}
/*******************************************************************/
/*                         avgSide functions                       */
/*******************************************************************/
/*             used to caLculate an aquisition IR reading          */
/*           performed at roBot init for grabbIng a valid range    */
/*             so that the normal IR average system taKes over     */
/*                                                                 */
/*        if the average fails to find any valid IR readings       */
/*            the value stays at 999 until a range is found        */
/*******************************************************************/
//---------------Average the front sensors for init----------------*/
int avgF(int L, int M1, int M2)                                  //*/
{ //*/
  int total = 0;                                                 //*/
  int div = 0;
  if ((midFCheck(M1)) || (midFCheck(M2))) //*/
  {
    if (midFCheck(M1))    //if mid range looks valid                 */
    { //*/
      total += M1;        //add to total                             */
      div += 1;          //update how many we accepted               */
    }                                                              //*/
    if (midFCheck(M2))    //if mid looks valid                       */
    { //*/
      total += M2;        //add to total                             */
      div += 1;         //update how many we accepted                */
    }
  }
  else if (longCheck(L))    //if long range looks valid                 */
  { //*/
    total += L;        //add to track total                        */
    div += 1;           //update how many we accepted              */
  }                                                              //*/
  //*/
  if (div != 0)      //as long as we got at least one value in     */
  { //*/
    return total / div;  // average our value                      */
  }                                                              //*/
  return 999;            //else remind us to check again           */
}                                                                //*/
//                                                                 */
//-----------------Average the back sensors for init-----------------
int avgB(int L, int M, int S1, int S2)                           //*/
{ //*/
  int total = 0;                                                 //*/
  int div = 0;                                                   //*/
  if (midCheck(M) || shortCheck(S1) || shortCheck(S2))
  { //*/
    if (midCheck(M))    //if mid range looks valid                   */
    { //*/
      total += M;        //add to total                              */
      div += 1;          //update how many we accepted               */
    }                                                              //*/
    if (shortCheck(S1))    // if short range looks valid             */
    { //*/
      total += S1;        //add to total                             */
      div += 1;         //update how many we accepted                */
    }                                                              //*/
    if (shortCheck(S2))    // if short range looks valid             */
    { //*/
      total += S2;        //add to total                             */
      div += 1;         //update how many we accepted                */
    }
  }  //*/
  else if (longCheck(L))    //if long range looks valid                 */
  { //*/
    total += L;        //add to track total                        */
    div += 1;           //update how many we accepted              */
  }
  if (div != 0)      //as long as we got at least one value in     */
  { //*/
    return total / div;  // average our value                      */
  }                                                              //*/
  return 999;            //else remind us to check again           */
}                                                                //*/
//                                                                 */
//-----------------average a side sensor array---------------------*/
int avgS(int L, int M)
{ //*/
  int total = 0;                                                 //*/
  int div = 0;
  if (midCheck(M))    //if mid looks valid                          */
  { //*/
    total += M;        //add to total                              */
    div += 1;         //update how many we accepted                */
  }      //*/
  else if (longCheck(L))    //if long range looks valid                 */
  { //*/
    total += L;        //add to track total                        */
    div += 1;           //update how many we accepted              */
  }                                                              //*/
  //*/
  if (div != 0)      //as long as we got at least one value in     */
  { //*/
    return total / div;  // average our value                      */
  }                                                              //*/
  return 999;            //else remind us to check again           */
}                                                                //*/



/*********************************************************************************************************/
/***********************************IR Selections Methods (per side)**************************************/
/*********************************************************************************************************/
/*      System essentially has memory of where it beLieved the values of the sensors to be before        */
/*          It takes all of the new readings and compares them to that previous value,                   */
/*            first decIding which order to check in based on last stored magnitude                      */
/*        then validating the range of the reading and finally comparing it to the last value            */
/*         to verify it is within the specified error tolerance (currently 30cm (2-26-14)                */
/*                                                                                                       */
/*      These algorithms are going to require review and eKpansion/subtraction to provide the            */
/*        cleanest and most reliaBle signal processing                                                   */
/*********************************************************************************************************/

//----------------------------------------Front IR processing--------------------------------------------------
int selectFront(int Long, int midL, int midR, int prev) {
  int check = avgF(IRLF, IRSFL, IRSFR);
  if (varIsAbout(check, prev, 25))
    return check;

  else if (prev > 165)  {                                                                                   //if our last value was out of the range of the mid IRs
    if (varIsAbout(Long, prev, updateRange) && longCheck(Long))                                           // if the long distance is roughly what we had last time
      return Long;                                                                                                   //use the Long sensor reading
    else if (midFCheck(midR) && midFCheck(midL) && varIsAbout(((midL + midR) / 2), prev, updateRange))        //else if the mids look good
      return ((midL + midR) / 2);                                                                              //use the average of the mid sensors
    else                                                                                                    //else the sensors are dirty or out of range
    return prev;                                                                                             //so use the old value for consistency
  }
  else {                                                                                                //since our last value was supposed to be in range of mid IRs
    if (varIsAbout(midL, midR, updateRange) && midFCheck(midR) && midFCheck(midL))                   //if the mid IRs agree within angles and prev value
      return ((midL + midR) / 2);                                                                                      //use the average of the mid sensors
    else if (longCheck(Long) && varIsAbout(Long, prev, updateRange * 2))                                                 //and the long range looks okay
      return Long;                                                                                                     //use the long range sensor
    else                                                                                                          //else the long was dirty/mids were dirty
    return prev;                                                                                                    //so use old value
  }
}
//------------------------------------- Side IR Processing Selection -----------------------------------------
int selectSide(int LongS, int midS, int prev) {
  int check = avgS(LongS, midS);
  if (varIsAbout(check, prev, 25))
    return check;
  else if (prev > 100)                                                 //if last reading was out of mid range view
  {
    if (longCheck(LongS) && varIsAbout(LongS, prev, updateRange))         //and the long value resembles and is valid
      return LongS;                                                                  //use the long range sensor
    else if (midCheck(midS) && varIsAbout(midS, prev, updateRange))           // if dirty or out of range and mid looks good
      return midS;                                                                  //use the mid range
    else                                                                      //if all were dirty or not in range or look like jumk
    return prev;                                                                  //leave the value alone
  }
  else                                                           //else last value was in range of mid IRs
  {
    if (midCheck(midS) && varIsAbout(midS, prev, updateRange))             // if mid looks good
      return midS;                                                              //use the mid range
    else if (longCheck(LongS) && varIsAbout(LongS, prev, updateRange * 2)) //else if the long value resembles and is valid
      return LongS;                                                             //use the long range sensor
    else                                                                   //if all were dirty or not in range or look like jumk
    return prev;                                                              //leave the value alone
  }
}


//----------------------------------Back IR update smarts----------------------------------------------
int selectBack(int LongB, int midB, int shortL, int shortR, int prev)
{
  if (varIsAbout((shortL + shortR) / 2, midB, 2) && midB > 6 && shortL > 3 && shortR > 3)  //OVERRIDE NORMAL SYSTEM-- if the shortRanges are confident
  {
    return (midB + shortL + shortR) / 3;                                                          //use them (keeps the system happy to go down to range( not good for effcient tuning))
  }
  int check = avgB(LongB, midB, shortL, shortR);
  if (varIsAbout(check, prev, 25))
    return check;
  else if (prev > 100)                                                                                     //if last reading was out of mid range view
  {
    if (longCheck(LongB) && varIsAbout(LongB, prev, updateRange))                                       //and the long value resembles and is valid
      return LongB;                                                                                                //use the long range sensor
    else if (midCheck(midB) && varIsAbout(midB, prev, updateRange))                                         // if dirty or out of range and mid looks good
      return midB;                                                                                                  //use the mid range
    else                                                                                                    //if all were dirty or not in range or look like jumk
    return prev;                                                                                                      //leave the value alone
  }
  else if (prev > 25)                                                                                   //else if last value was in range of mid IRs (outside of short ish)
  {
    if (midCheck(midB) && varIsAbout(midB, prev, updateRange))                                                     // if mid looks good
      return midB;                                                                                                    //use the mid range
    else if (shortCheck(shortL) && shortCheck(shortR) && varIsAbout(((shortL + shortR) / 2), prev, updateRange))  //else if short looks good
      return (shortL + shortR) / 2;                                                                                    //use the average
    else if (longCheck(LongB) && varIsAbout(LongB, prev, updateRange))                                             //else if the long value resembles and is valid
      return LongB;                                                                                                  //use the long range sensor
    else                                                                                                          //if all were dirty or not in range or look like jumk
    return prev;                                                                                                //leave the value alone
  }
  else if (prev < 25)                                                                                      //else if the last value was in short range
  {
    if (shortCheck(shortL) && shortCheck(shortR) && varIsAbout(((shortL + shortR) / 2), prev, updateRange))      //if shorts look good !!together!! <--- might be bad way to check due to angle (but mid should see any range that could happen
      return (shortL + shortR) / 2;                                                                                        //return average of shorts
    else if (midCheck(midB) && varIsAbout(midB, prev, updateRange))                                              //else if mid looks good
      return midB;                                                                                                        //use the mid range
    else if (longCheck(LongB) && varIsAbout(LongB, prev, updateRange))                                           //else ifthe long value resembles and is valid
      return LongB;                                                                                                  //use the long range sensor
    else                                                                                                         //else all were dirty or not in range or look like jumk
    return prev;                                                                                                          //leave the value alone
  }
}


