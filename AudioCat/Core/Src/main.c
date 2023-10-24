/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "SD/fatfs.h"
#include "wav_header.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

SD_HandleTypeDef hsd1;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_MEMORYMAP_Init(void);
static void MX_ADC1_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
void myprintf(const char *fmt, ...);
void header_to_sd(wav_header* header, FIL* fil, UINT* bw);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define FILTER true

void myprintf(const char *fmt, ...){
	static char buffer[256];
	va_list args;

	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	int len= strlen(buffer);
	HAL_UART_Transmit(&huart4, (uint8_t*)buffer, len, -1);
}

void header_to_sd(wav_header* header, FIL* fil, UINT* bw){
	myprintf("start writing header");
	f_write(fil, &header->riff_header, 4, bw);
	f_write(fil, &header->wav_size, 4 , bw);
	f_write(fil, &header->wave_header, 4, bw);
	myprintf("finished RIFF header");
	f_write(fil, &header->fmt_header, 4, bw);
	f_write(fil, &header->fmt_chunk_size, 4 , bw);
	f_write(fil, &header->audio_format, 2 , bw);
	f_write(fil, &header->num_channels, 2 , bw);
	f_write(fil, &header->sample_rate, 4 , bw);
	f_write(fil, &header->byte_rate, 4 , bw);
	f_write(fil, &header->sample_alignment, 2 , bw);
	f_write(fil, &header->bit_depth, 2 , bw);
	f_write(fil, header->data_header, 4, bw);
	f_write(fil, &header->data_bytes, 4 , bw);
	myprintf("Finished writing header");
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint16_t count=0;
	  uint32_t readBuf[50000];
	  uint8_t readBuf_8b[50000];
	  uint16_t readBuf_16b[50000];
	  char filename[256];
	  uint16_t raw;
    char msg[10];
    uint8_t header_size=8;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_MEMORYMAP_Init();
  MX_ADC1_Init();
  MX_SDMMC1_SD_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  MX_FATFS_Init();
  myprintf("\r\n~ SD card demo ~\r \n\r\n");
  HAL_Delay(1000);

  FATFS FatFs;
  FIL fil;
  FRESULT fres;

  fres= f_mount(&FatFs, "/", 1);
  if(fres!= FR_OK)
  {
	  myprintf("f_mount error (%i) \r\n", fres);
	  while(1);
  }

  DWORD free_clusters, free_sectors, total_sectors;

  FATFS* getFreeFs;

  fres= f_getfree("", &free_clusters, &getFreeFs);
  if (fres != FR_OK) {
	  myprintf("f_getfree error (%i)\r\n",fres);
	  while(1);
  }

  total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
  free_sectors = free_clusters * getFreeFs->csize;

  myprintf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

  bw_filter filt = create_filter(1000, 27027);

  // fres = f_open(&fil, "/write.txt", FA_READ);
    //   if (fres != FR_OK) {
  	// 	myprintf("f_open error (%i)\r\n");
  	// 	while(1);
    //   }
  //   myprintf("I was able to open 'test.txt' for reading!\r\n");
    //   BYTE readBuf[30];

    //   TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
      //     if(rres != 0) {
    	//   	myprintf("Read string from 'test.txt' contents: %s\r\n", readBuf);
      //     } else {
    	//   	myprintf("f_gets error (%i)\r\n", fres);
      //     }
  //     f_close(&fil);

	  //   fres = f_open(&fil, "write.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	// if(fres == FR_OK) {
	// myprintf("I was able to open 'write.txt' for writing\r\n");
	// } else {
	// myprintf("f_open error (%i)\r\n", fres);
	// }
	// strncpy((char*)readBuf, "a new file is made!", 19);
	  UINT bytesWrote;
	  //   fres = f_write(&fil, readBuf, 19, &bytesWrote);
	  //   if(fres == FR_OK) {
		// 	myprintf("Wrote %i bytes to 'write.txt'!\r\n", bytesWrote);
	  //   } else {
		// 	myprintf("f_write error (%i)\r\n");
	  //   }

	  //   f_close(&fil);

	  //   f_mount(NULL, "", 0);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
//	  sprintf(msg, "%hu\r\n", raw);
//	  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	  HAL_Delay(1);
    
    if (count<5) {
	  sprintf(filename, "r_%05d.wav",  count++);
	  fres = f_open(&fil, filename, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);

	  if (fres == FR_OK) {
		  myprintf("I was able to open %s for writing\r\n",filename);
	  } else {
		  myprintf("f_open error (%i)\r\n", fres);
	  }

//	  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
//	  HAL_Delay(1000);

//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1);

	  wav_header header = create_PCM_SC_header_correct(50000);
	  UINT bw;
//	  fres = f_write(&fil, (to_byte_array(header)), 44, &bw);
//	  myprintf("wav_size: %d\r\n", header.wav_size);
//	  myprintf("data_size: %d\r\n", header.data_bytes);
//	  myprintf("data: %x\r\n", header.data_bytes);
//	  myprintf("swapped manual: \r\n%x\r\n", ((header.data_bytes<<24) & 0xff000000) |
//			  ((header.data_bytes<<8) & 0x00ff0000) |
//			  ((header.data_bytes>>8) & 0x0000ff00) |
//			((header.data_bytes>>24) & 0x000000ff) );
//	  uint32_t swapped = endian_swap_32_ret(header.data_bytes);
	  myprintf("fmt_chunk_size: %d\r\n", header.fmt_chunk_size);
	  myprintf("fmt_chunk_size: %x\r\n", header.fmt_chunk_size);


//	  endian_swap(&swapped, header.data_bytes);
//	  myprintf("data_size swapped: %d\r\n", swapped);
//	  myprintf("data_size swapped hex: %x\r\n", swapped);
	  header_to_sd(&header, &fil, &bw);
	  
//	  char h[37];
//	  sprintf(h, ((char*) &header), sizeof(header));
//	  h[37] = 0x00;
//	  myprintf("Header, size: %d, cont: %s\r\n", h);

	  uint32_t start = HAL_GetTick();
	  myprintf("Clock at start: %d \r\n", start);
	  for (int i=0; i<50000; i++) { // Used to be i+=2. Changed it to i+=1. Also increased size from 5 to 25000, changed buffer to 32 bit
//		endian_swap(&(readBuf[i]), HAL_ADC_GetValue(&hadc1));
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
#if FILTER
		readBuf_16b[i] = filter(filt, (HAL_ADC_GetValue(&hadc1) & 0x0000ffff));
#else
		readBuf_16b[i] = (HAL_ADC_GetValue(&hadc1) & 0x0000ffff);
#endif
//		for (int i = 1; i < 22; i++) {
//			HAL_ADC_GetValue(&hadc1);
//		}
	  }
	  uint32_t end = HAL_GetTick();

	  myprintf("Clock at end: %d\r\n", end);
	  myprintf("Record time: %d ms\r\n", (end - start));

	  myprintf("First value: %x", readBuf_16b[0]);

	  fres = f_write(&fil,&readBuf_16b, 50000 * 2, &bytesWrote);
	  count++;

	  if(fres == FR_OK) {
			myprintf("written to file\r\n");
	  } else {
			myprintf("f_write error (%i)\r\n");
	  }

	  f_close(&fil);
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 5;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 24576;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
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

/**
  * @brief MEMORYMAP Initialization Function
  * @param None
  * @retval None
  */
static void MX_MEMORYMAP_Init(void)
{

  /* USER CODE BEGIN MEMORYMAP_Init 0 */

  /* USER CODE END MEMORYMAP_Init 0 */

  /* USER CODE BEGIN MEMORYMAP_Init 1 */

  /* USER CODE END MEMORYMAP_Init 1 */
  /* USER CODE BEGIN MEMORYMAP_Init 2 */

  /* USER CODE END MEMORYMAP_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  if (HAL_SD_Init(&hsd1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
