


void rotateLeft(int increment)
{
  pos=pos-increment;
  pos=constrain(pos,MINANGLE_SERVO,MAXANGLE_SERVO);
  myservo.write(pos);
  return; 
}
void rotateRight(int increment)
{
  pos=pos+increment;
  pos=constrain(pos,MINANGLE_SERVO,MAXANGLE_SERVO);
  myservo.write(pos);
  return;
}
