/**
 * @file board_configuration.cpp
 */

#include "pch.h"
#include "board_overrides.h"

static void setDefaultFrankensoStepperIdleParameters() {
	engineConfiguration->idle.stepperDirectionPin = Gpio::E10;
	engineConfiguration->idle.stepperStepPin = Gpio::E9;
	engineConfiguration->stepperEnablePin = Gpio::E8;
	engineConfiguration->idleStepperReactionTime = 10;
	engineConfiguration->idleStepperTotalSteps = 150;
}

static void setCanFrankensoDefaults() {
	engineConfiguration->canTxPin = Gpio::B9;
	engineConfiguration->canRxPin = Gpio::B8;
	
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_3_4_2;
}

Gpio getWarningLedPin() {
    // open question if we need those LEDs at all? shall those be configurable?
	return Gpio::C8;
}

Gpio getCommsLedPin() {
	return Gpio::A1;
}

Gpio getRunningLedPin() {
    // open question if we need those LEDs at all? shall those be configurable?
	return Gpio::Unassigned;
}

#if EFI_ONBOARD_MEMS
static void configureAccelerometerPins() {
//	engineConfiguration->accelerometerCsPin = Gpio::D11; // we have a conflict with VVT output on Miata
// 	engineConfiguration->is_enabled_spi_1 = true; // we have a conflict with PA5 input pin

	// stm32f4discovery defaults
	engineConfiguration->spi1mosiPin = Gpio::A7;
	engineConfiguration->spi1misoPin = Gpio::A6;
	engineConfiguration->spi1sckPin = Gpio::A5;
}
#endif // EFI_ONBOARD_MEMS

/**
 * @brief	Hardware board-specific default configuration (GPIO pins, ADC channels, SPI configs etc.)
 */
void setBoardDefaultConfiguration() {
	setDefaultFrankensoStepperIdleParameters();
	setCanFrankensoDefaults();


	// set optional subsystem configs
#if EFI_ONBOARD_MEMS
	// this would override some values from above
	configureAccelerometerPins();
#endif /* EFI_ONBOARD_MEMS */



	engineConfiguration->map.sensor.hwChannel = EFI_ADC_4;
	engineConfiguration->clt.adcChannel = EFI_ADC_3;
	engineConfiguration->iat.adcChannel = EFI_ADC_4;
	engineConfiguration->afr.hwChannel = EFI_ADC_14;

	engineConfiguration->accelerometerSpiDevice = SPI_DEVICE_3;

	engineConfiguration->triggerSimulatorPins[0] = Gpio::E14;
	engineConfiguration->triggerSimulatorPins[1] = Gpio::E15;

	engineConfiguration->triggerInputPins[0] = Gpio::C4;
//	engineConfiguration->triggerInputPins[1] = Gpio::A5;

	// set this to SPI_DEVICE_3 to enable stimulation
	//engineConfiguration->digitalPotentiometerSpiDevice = SPI_DEVICE_3;
	engineConfiguration->digitalPotentiometerChipSelect[0] = Gpio::B0;
	engineConfiguration->digitalPotentiometerChipSelect[1] = Gpio::Unassigned;
	engineConfiguration->digitalPotentiometerChipSelect[2] = Gpio::B1;
	engineConfiguration->digitalPotentiometerChipSelect[3] = Gpio::Unassigned;

	engineConfiguration->spi1mosiPin = Gpio::C12;
	engineConfiguration->spi1misoPin = Gpio::C11;
	engineConfiguration->spi1sckPin = Gpio::C10; // please note that this pin is also SWO/SWD - Single Wire debug Output

	engineConfiguration->spi2mosiPin = Gpio::B15;
	engineConfiguration->spi2misoPin = Gpio::B14;
	engineConfiguration->spi2sckPin = Gpio::B13;

	engineConfiguration->spi3mosiPin = Gpio::C12;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3sckPin = Gpio::C10;



#if EFI_FILE_LOGGING
	setDefaultSdCardParameters();
#endif /* EFI_FILE_LOGGING */

	engineConfiguration->is_enabled_spi_1 = false;
	engineConfiguration->is_enabled_spi_2 = false;
	engineConfiguration->is_enabled_spi_3 = true;

}
