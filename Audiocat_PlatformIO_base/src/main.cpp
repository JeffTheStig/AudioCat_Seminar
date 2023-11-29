#include <Arduino.h>
// #include <STM32SD.h>
#include <SPI.h>
#include "bme68xLibrary.h"

// Bme68x bme;
#include <SD.h>
// #ifndef PIN_CS
// #define PIN_CS SS
// #endif

Bme68x bme;
// Sd2Card card;
// SdFatFs fatFs;
// #define SD_DETECT_PIN SD_DETECT_NONE
// set RX and TX pins
// HardwareSerial Serial4(PA1, PA0);
File wavFile;
int loop_Val=0;
int begin = 0;
ADC_HandleTypeDef hadc1;

uint16_t buffer[100000];
const char* filename = "data.wav";
/// The first 4 byte of a wav file should be the characters "RIFF" */
char chunkID[4] = {'R', 'I', 'F', 'F'};
/// 36 + SubChunk2Size
uint32_t chunkSize = 2 * 10000; // You Don't know this until you write your data but at a minimum it is 36 for an empty file
/// "should be characters "WAVE"
uint32_t filesize = 36 + chunkSize;
char format[4] = {'W', 'A', 'V', 'E'};
/// " This should be the letters "fmt ", note the space character
char subChunk1ID[4] = {'f', 'm', 't', ' '};
///: For PCM == 16, since audioFormat == uint16_t
uint32_t subChunk1Size = 16;
///: For PCM this is 1, other values indicate compression
uint16_t audioFormat = 1;
///: Mono = 1, Stereo = 2, etc.
uint16_t numChannels = 1;
///: Sample Rate of file
uint32_t sampleRate = 40000;
///: SampleRate * NumChannels * BitsPerSample/8
uint32_t byteRate = 40000 * 2;
///: The number of byte for one frame NumChannels * BitsPerSample/8
uint16_t blockAlign = 2;
///: 8 bits = 8, 16 bits = 16
uint16_t bitsPerSample = 14;
///: Contains the letters "data"
char subChunk2ID[4] = {'d', 'a', 't', 'a'};
///: == NumSamples * NumChannels * BitsPerSample/8  i.e. number of byte in the data.
uint32_t subChunk2Size = 0; // You Don't know this until you write your data
void writeWavHeader()
{
   wavFile.seek(0);
   wavFile.write(chunkID,4);
   wavFile.write((byte*)&filesize,4);
   wavFile.write(format,4);
   wavFile.write(subChunk1ID,4);
   wavFile.write((byte*)&subChunk1Size,4);
   wavFile.write((byte*)&audioFormat,2);
   wavFile.write((byte*)&numChannels,2);
   wavFile.write((byte*)&sampleRate,4);
   wavFile.write((byte*)&byteRate,4);
   wavFile.write((byte*)&blockAlign,2);
   wavFile.write((byte*)&bitsPerSample,2);
   wavFile.write(subChunk2ID,4);
   wavFile.write((byte*)&chunkSize,4);
}
void writeDataToWavFile(uint16_t *data)
{
  // if(loop_Val>1000)
  // {
  //   wavFile.close();
  //   while(1);
  // }
  // else
  // {
  // int16_t sampleValue = map(data, 0, 32767,-32767,32767);

  // subChunk2Size += numChannels * bitsPerSample/8;
  wavFile.seek(40);
  for(int i = 0; i < 100000; i++)
  {
    wavFile.write((uint8_t*)&data[i],2);
  }
  // wavFile.write((uint8_t*)&data,20000);
  wavFile.close();
   Serial.println(wavFile.size());

  // wavFile.seek(4);
  // chunkSize = 36 + subChunk2Size;
  // wavFile.write((byte*)&chunkSize,4);

  // wavFile.seek(wavFile.size()-1);
  // wavFile.write((byte*)&sampleValue,2);
  // Serial.println("Data written to file...");
  // }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
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
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_391CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    while(1);
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void setup() {
  // put your setup code here, to run once:
  // Serial4.begin(9600);
  Serial.setRx(PA10);
  Serial.setTx(PA9);
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  //Begin BME68X interfacing
  Wire.begin();
  bme.begin(0x77, Wire);
  	if(bme.checkStatus())
	{
		if (bme.checkStatus() == BME68X_ERROR)
		{
			Serial.println("Sensor error:" + bme.statusString());
			return;
		}
		else if (bme.checkStatus() == BME68X_WARNING)
		{
			Serial.println("Sensor Warning:" + bme.statusString());
		}
	}
  	bme.setTPH();
    bme.setHeaterProf(300, 100);
    Serial.println("TimeStamp(ms), Temperature(deg C), Pressure(Pa), Humidity(%), Gas resistance(ohm), Status");
 

  MX_ADC1_Init();
  // 	Wire.begin();
  //   bme.begin(0x77, Wire);
  //   	if(bme.checkStatus())
	// {
	// 	if (bme.checkStatus() == BME68X_ERROR)
	// 	{
	// 		Serial.println("Sensor error:" + bme.statusString());
	// 		return;
	// 	}
	// 	else if (bme.checkStatus() == BME68X_WARNING)
	// 	{
	// 		Serial.println("Sensor Warning:" + bme.statusString());
	// 	}
	// }
  	// bme.setTPH();
    // bme.setHeaterProf(300, 100);
    // Serial.println("TimeStamp(ms), Temperature(deg C), Pressure(Pa), Humidity(%), Gas resistance(ohm), Status");
  // Serial.println("Hello there!");
/* Commenting out SD card code to enable BME
  Serial.println("Initializing SD card...");
  SPI.setMISO(PA6);//MISO
  SPI.setMOSI(PA7);//MOSI
  SPI.setSCLK(PA5);
  if (!SD.begin(PD14)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("card initialized.");
  // Serial.println("Creating example.txt...");
    wavFile = SD.open(filename, FILE_WRITE);


  if (!wavFile)
    while (1);

  writeWavHeader();
  Serial.println("Header created!"); */
  // myFile.close();
  //   if (SD.exists("example.txt")) {
  //   Serial.println("example.txt exists.");
  // } else {
  //   Serial.println("example.txt doesn't exist.");
  // }
  // Serial.print("Initializing SD card...");
  // SD.setDx(PC8, PC9, PC10, PC11);
  // SD.setCMD(PD2);
  // SD.setCK(PC12); // using PinName
  // see if the card is present and can be initialized:
  // while (!SD.begin(SD_DETECT_NONE))
  // {
  //   Serial.print("looking for card!");
  //   delay(100);
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


  // pinMode(PC7, OUTPUT);
  // pinMode(PG4, OUTPUT);

  // card.setDx(PC8, SD_DETECT_NONE, SD_DETECT_NONE, SD_DETECT_NONE);
  // card.setCMD(PD2);
  // card.setCK(PC12);
  
  // while(!card.init()) {
  //   // Serial4.println("initialization failed. Is a card inserted?");
  //   delay(10);
  // }

  // while (!fatFs.init()) {
  //   Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
  //   delay(10);
  // }
  begin = millis();
}

void loop() {
  // if (loop_Val >= 10000) {
  //   Serial.printf("Analog reading took %d ms", millis()-begin);
  //   while(1);
  // }
  // put your main code here, to run repeatedly:
  // Serial.println("Hello World!");
  // loop_Val++;
  // digitalWrite(PC7, HIGH); // sets the digital pin 13 on
  // digitalWrite(PG4, HIGH);
  // delay(1000);
  // char filename[100] = "r_00000.wav";
  // for(int i = 0; i < 5; i++)
  // {
  //   sprintf(filename, "x_%05d.wav",  i);
  //   Serial.println(filename);
    // myFile = SD.open(filename, FILE_WRITE);

    // buffer[loop_Val] = (uint8_t) analogRead(PC2);
    // loop_Val++;
    /* this is commented out for enabling BME
    int start = millis();
    for (int i=0; i<100000; i++) { // Used to be i+=2. Changed it to i+=1. Also increased size from 5 to 25000, changed buffer to 32 bit
      HAL_ADC_Start(&hadc1);
      HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
      buffer[i] = (HAL_ADC_GetValue(&hadc1) & 0x0000ffff);
    }
    Serial.printf("Analog reading (STM) took %d ms", millis()-start);
    // delay(1000);
    writeDataToWavFile(&buffer[0]); */
      // dataString += String(sensor);
    // if(myFile){
    //   myFile.println(buffer);
    //   Serial.println("Written to file...");
    //   Serial.println(myFile.size());
    //   myFile.close();
    // }
    
  // }
  // Serial.println(dataString);
  // dataString += String(sensor);            // waits for a second
  // Serial4.println(sensor);
  // bme68xData data;

	// bme.setOpMode(BME68X_FORCED_MODE);
	// delayMicroseconds(bme.getMeasDur());

	// if (bme.fetchData())
	// {
	// 	bme.getData(data);
	// 	Serial.print(String(millis()) + ", ");
	// 	Serial.print(String(data.temperature) + ", ");
	// 	Serial.print(String(data.pressure) + ", ");
	// 	Serial.print(String(data.humidity) + ", ");
	// 	Serial.print(String(data.gas_resistance) + ", ");
	// 	Serial.println(data.status, HEX);
	// }
  // digitalWrite(PC7, LOW);  // sets the digital pin 13 off
  // digitalWrite(PG4, LOW);
  // delay(1000);            // waits for a second
  // delay(1000);
  bme68xData data;

	bme.setOpMode(BME68X_FORCED_MODE);
	delayMicroseconds(bme.getMeasDur());

	if (bme.fetchData())
	{
		bme.getData(data);
		Serial.print(String(millis()) + ", ");
		Serial.print(String(data.temperature) + ", ");
		Serial.print(String(data.pressure) + ", ");
		Serial.print(String(data.humidity) + ", ");
		Serial.print(String(data.gas_resistance) + ", ");
		Serial.println(data.status, HEX);
	}
}
