struct BMSFaults {
  bool cellOvervoltage;
  bool cellUndervoltage;
  bool packOvervoltage;
  bool packUndervoltage;
  bool overtemperature;
};

extern BMSFaults faults;

void clearFaults();
bool hasFault();
void updateFaults();