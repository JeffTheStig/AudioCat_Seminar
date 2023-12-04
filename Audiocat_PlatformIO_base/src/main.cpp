#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include "bme68xLibrary.h"

#include <SD.h>
#include "wav_header.h"

#define SAMPLE_SIZE 100000 // Sample size set to 100,000 samples 

Bme68x bme;
File wavFile;
char wavFilename[32];
File envFile;
char envFilename[32];
int fileCount = 0;
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

void headerToSd(wav_header* header) {
  wavFile.seek(0);
	Serial.println("start writing header");
	wavFile.write(header->riff_header, 4);
	wavFile.write((uint8_t*) &(header->wav_size), 4);
	wavFile.write(header->wave_header, 4);
	Serial.println("finished RIFF header");
	wavFile.write(header->fmt_header, 4);
	wavFile.write((uint8_t*) &(header->fmt_chunk_size), 4);
	wavFile.write((uint8_t*) &(header->audio_format), 2);
	wavFile.write((uint8_t*) &(header->num_channels), 2);
	wavFile.write((uint8_t*) &(header->sample_rate), 4);
	wavFile.write((uint8_t*) &(header->byte_rate), 4);
	wavFile.write((uint8_t*) &(header->sample_alignment), 2);
	wavFile.write((uint8_t*) &(header->bit_depth), 2);
	wavFile.write(header->data_header, 4);
	wavFile.write((uint8_t*) &(header->data_bytes), 4);
	Serial.println("Finished writing header");
}
void writeDataToWavFile(uint16_t *data)
{
  // wavFile.seek(44);
  for(int i = 0; i < SAMPLE_SIZE; i++)
  {
    wavFile.write((uint8_t*)&data[i],2);
  }
  Serial.printf("Wav file size: %d\r\n", wavFile.size());
  wavFile.close();
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void) {


  ADC_ChannelConfTypeDef sConfig = {0};

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

}

void setup() {
  Serial.setRx(PA10);
  Serial.setTx(PA9);
  Serial.begin(115200);
  
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
  bme.fetchData();
  bme68xData data;
  bme.getData(data);

  MX_ADC1_Init();

  pinMode(PC13, INPUT); // User button
  pinMode(PC7, OUTPUT); // User LED1

  // Commenting out SD card code to enable BME
  // SD card setup
  Serial.println("Initializing SD card...");
  SPI.setMISO(PA6);//MISO
  SPI.setMOSI(PA7);//MOSI
  SPI.setSCLK(PA5);
  if (!SD.begin(PD14)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("card initialized.");

  sprintf(wavFilename, "R_%05d.WAV", fileCount + 1);
  while(SD.exists(wavFilename)) {
    sprintf(wavFilename, "R_%05d.WAV", ++fileCount + 1); // Find next file name.
  }

  Serial.printf("Starting at filecount: %d\r\n", fileCount);

  pinMode(PB7, OUTPUT);
  digitalWrite(PB7, HIGH); // Turn on blue LED to indicate the setup process is finished.

  Serial.println("Booting complete...starting loop");
  begin = millis();
}

void loop() {

  if (digitalRead(PC13) == HIGH) { // If button is pressed
    digitalWrite(PC7, HIGH);

    sprintf(wavFilename, "r_%05d.wav", ++fileCount);
    Serial.printf("Deleting file: %s, Status: %d\r\n", wavFilename, SD.remove(wavFilename));
    wavFile = SD.open(wavFilename, FILE_WRITE);

    if (!wavFile)
      while (1);

    // writeWavHeader();
    wav_header header = create_PCM_SC_header_correct(SAMPLE_SIZE); // Create a new wav header.
    headerToSd(&header);
    Serial.println("Header created!"); 

    int start = millis();
    for (int i=0; i < SAMPLE_SIZE; i++) { // Read SAMPLE_SIZE ADC samples
      HAL_ADC_Start(&hadc1);
      HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
      buffer[i] = (HAL_ADC_GetValue(&hadc1) & 0x0000ffff);
    }
    Serial.printf("Analog reading (STM) took %d ms\r\n", millis()-start);
    
    writeDataToWavFile(&buffer[0]);

    wavFile.close();

    bme68xData data;
    DynamicJsonDocument doc(1024);

    bme.setOpMode(BME68X_FORCED_MODE);
    delayMicroseconds(bme.getMeasDur());

    if (bme.fetchData()) {
      bme.getData(data);
      Serial.print(String(millis()) + ", ");
      Serial.print(String(data.temperature) + ", ");
      Serial.print(String(data.pressure) + ", ");
      Serial.print(String(data.humidity) + ", ");
      Serial.print(String(data.gas_resistance) + ", ");
      Serial.println(data.status, HEX);

      doc["time"] = start;
      doc["temperature"] = data.temperature;
      doc["pressure"] = data.pressure;
      doc["humidity"] = data.humidity;
      doc["gas_resistance"] = data.gas_resistance;
    }

    sprintf(envFilename, "d_%05d.jsn", fileCount);
    Serial.printf("Deleting file: %s, Status: %d\r\n", envFilename, SD.remove(envFilename));
    envFile = SD.open(envFilename, FILE_WRITE);

    Serial.printf("Filename: %s\r\n", envFilename);

    String datOut = "";
    serializeJson(doc, datOut);

    char output[512];
    datOut.toCharArray(output, 512);
    Serial.println(output);
    envFile.write(output, datOut.length());
    Serial.printf("envFile size: %d\r\n", envFile.size());
    envFile.close();

    digitalWrite(PC7, LOW);

  }

  
}
