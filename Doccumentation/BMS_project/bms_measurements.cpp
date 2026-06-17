void bmsReadMeasurements() {
  bq76952ReadCellVoltages(cellVoltage_mV);
  bq76952ReadPackVoltage(pack.packVoltage_mV);
  bq76952ReadCurrent(pack.current_A);
  bq76952ReadTemperatures(cellTemp_C);

  // update pack.cells[]
  // calculate min, max, average
}