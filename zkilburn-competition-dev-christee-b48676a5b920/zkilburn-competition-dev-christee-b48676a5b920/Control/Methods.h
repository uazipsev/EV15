inline void packetWait();
inline void ledUpdate();
//screen.h
inline static bool writeObject(byte object, byte index, unsigned int data);
inline int calcAndConstrainHeading(int calcHeading);
inline int calcOutputHeading(int in);
inline static bool readObject();
inline void writeScreen();
inline static bool readStream();
inline static bool writeContrast(int value);

inline void commSafety();
//macroControl.h
inline void ensureReceived(bool complete);

void sendDataMotor(int actuator);
void sendDataMotor(int leftMotor, int rightMotor, int actuator);
void sendDataMotor(int leftMotor, int rightMotor);
void sendDataNavigation(int _macro_command);
void sendDataNavigation(int _macro_command, int _macro_sub_command, int _macro_stop);
void sendLEDdata(int stateOverride, int colorPicker);
void updateScreen();
