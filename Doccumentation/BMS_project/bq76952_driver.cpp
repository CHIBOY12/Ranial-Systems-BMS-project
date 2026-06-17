bool bq76952Init();
bool bq76952ReadCellVoltages(int cellVoltage_mV[16]);
bool bq76952ReadPackVoltage(long &packVoltage_mV);
bool bq76952ReadCurrent(float &current_A);
bool bq76952ReadTemperatures(int cellTemp_C[16]);
bool bq76952ReadFaults();
bool bq76952SetFETs(bool chargeOn, bool dischargeOn);
bool bq76952SetBalancing(uint16_t balanceMask);