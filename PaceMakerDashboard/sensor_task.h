// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Sensor Task
//  Runs on Core 1: reads sensors, detects alerts, drives buzzer/OLED
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_SENSOR_TASK_H
#define MEDIPULSE_SENSOR_TASK_H

// FreeRTOS task entry point — pinned to SENSOR_CORE
void sensorTask(void* param);

#endif // MEDIPULSE_SENSOR_TASK_H
