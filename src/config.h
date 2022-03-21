#pragma once

// lcd
static constexpr int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

static constexpr int btn = 10;

static constexpr int inputpwr = A4;
static constexpr int inputgnd = A5;
static constexpr int input = A6;

static constexpr float maxDist = 100; // mm

static constexpr int numSamples = 200;

static constexpr int refreshInterval = 500; // ms
static constexpr int sampleFreq = 500;

static const float calPoints[] = { 15, 20, 25, 30, 40, 50, 60, 80, 100 };
static constexpr int numCals = sizeof(calPoints) / sizeof(calPoints[0]);
