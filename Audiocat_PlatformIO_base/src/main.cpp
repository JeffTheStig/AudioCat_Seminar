#include <Arduino.h>
#include <STM32SD.h>

#define SD_FET_EN             PE3
#define SRAM_FET_EN           PE2
#define GPS_FET_EN            PE0
#define RADIO_FET_EN          PB4
#define MIC_US_FET_EN         PB0
#define OPAMP_LP_FET_EN       PD13
#define BMI088_FET_EN         PC2
#define BME688_FET_EN         PB10
#define BH1749NUC_FET_EN      PB1
#define LDO_1V0_EN            PA3

#define MIC_US_OUT            PA5
#define MIC_LP_OUT            PA4
#define MIC_LP_OUT_ALT        PC3

Sd2Card card;
SdFatFs fatFs;
uint32_t lastSample = 0;
int adc1_read = 0;
ADC_HandleTypeDef hadc1;

// set RX and TX pins
// HardwareSerial Serial4(PA1, PA0);
File dataFile;

static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_14B;
  hadc1.Init.GainCompensation = 0;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_5CYCLE;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void setup() {
  // put your setup code here, to run once:
  // Serial4.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Hello there!");
  MX_ADC1_Init();

  // Serial.print("Initializing SD card...");
  // SD.setDx(PC8, PC9, PC10, PC11);
  // SD.setCMD(PD2);
  // SD.setCK(PC12); // using PinName
  // // see if the card is present and can be initialized:
  // while (!SD.begin())
  // {
  //   Serial.print("looking for card!");
  //   delay(10);
  // }
  // delay(100);
  // Serial.println("card initialized.");

  // // open the file. note that only one file can be open at a time,
  // // so you have to close this one before opening another.
  // dataFile = SD.open("datalog.txt", FILE_WRITE);
  // // if the file is available, seek to last position
  // if (dataFile) {
  //   dataFile.seek(dataFile.size());
  // }
  // // if the file isn't open, pop up an error:
  // else {
  //   Serial.println("error opening datalog.txt");
  // }


  pinMode(PG3, OUTPUT);
  pinMode(PG4, OUTPUT);

  // Setup open-drain for enable pin
  pinMode(MIC_US_FET_EN, OUTPUT);
  digitalWrite (MIC_US_FET_EN, HIGH);
  pinMode(OPAMP_LP_FET_EN, OUTPUT_OPEN_DRAIN);
  digitalWrite(OPAMP_LP_FET_EN, HIGH);
  pinMode(SD_FET_EN, OUTPUT_OPEN_DRAIN);
  digitalWrite(SD_FET_EN, HIGH);
  pinMode(SRAM_FET_EN, OUTPUT_OPEN_DRAIN);
  digitalWrite(SRAM_FET_EN, HIGH);
  // pinMode(MIC_US_FET_EN, INPUT_FLOATING);
  // pinMode(OPAMP_LP_FET_EN, INPUT_FLOATING);
  // pinMode(SD_FET_EN, INPUT_FLOATING);


  card.setDx(PC8, PC9, PC10, PC11);
  card.setCMD(PD2);
  card.setCK(PC12);
  // card.setCKIN(NUM_DIGITAL_PINS);
  // card.setCDIR(NUM_DIGITAL_PINS);
  // card.setDxDIR(NUM_DIGITAL_PINS, NUM_DIGITAL_PINS);

  Serial.println("Initializing SD card");
  while (!card.init(SD_DETECT_NONE)) {
    Serial.println("initialization failed. Is a card inserted?");
    delay(10);
  }
    // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  analogReadResolution(14);

  Serial.println("Initializing FatFS");
  while (!fatFs.init()) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    digitalWrite(PG3, HIGH);
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Hello World!");
  // if (millis() - lastSample > 100) { // Every 100ms:
  //       lastSample = millis();
  //       adc1_read = 0;
  //       digitalWrite(PG3, HIGH); // sets the digital pin 13 on
  //       digitalWrite(PG4, HIGH);
  //   }
  //   int reading = analogRead(PA5);
  //   if (reading > adc1_read) {
  //       adc1_read = reading;
  //       digitalWrite(PG3, LOW);  // sets the digital pin 13 off
  //       digitalWrite(PG4, LOW);
  //   }
  // HAL_ADC_Start(&hadc1);
	// HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  // adc1_read = HAL_ADC_GetValue(&hadc1);
  adc1_read = analogRead(PA5);
  Serial.printf("%8x\r\n", adc1_read);

  // String dataString = "";
  // int sensor = analogRead(A1);
  // dataString += String(sensor);            // waits for a second
  // Serial4.println(dataString);
  // delay(10);
  // delay(1000);            // waits for a second
}
