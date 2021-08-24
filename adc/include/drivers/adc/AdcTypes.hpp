#ifndef DRIVERS_ADC_INCLUDE_DRIVERS_ADC_ADCTYPES_HPP
#define DRIVERS_ADC_INCLUDE_DRIVERS_ADC_ADCTYPES_HPP

#include <cstdint>
#include <callbacks/Callback.hpp>

namespace Drivers {

  /// @brief Which ADC peripheral to use.
  enum class AdcPort : uint16_t {
    Adc1 = 0U,
    Adc2 [[maybe_unused]] = 1U
  };

  ///@brief THe channel to take the reading on
  enum class AdcChannel : uint16_t {
    AdcChannel0 [[maybe_unused]] = 0,
    AdcChannel1 [[maybe_unused]] = 1,
    AdcChannel2 [[maybe_unused]] = 2,
    AdcChannel3 [[maybe_unused]] = 3,
    AdcChannel4 [[maybe_unused]] = 4,
    AdcChannel5 [[maybe_unused]] = 5,
    AdcChannel6 [[maybe_unused]] = 6,
    AdcChannel7 [[maybe_unused]] = 7,
    AdcChannel8 [[maybe_unused]] = 8,
    AdcChannel9 [[maybe_unused]] = 9,
    AdcChannel10 [[maybe_unused]] = 10,
    AdcChannel11 [[maybe_unused]] = 11,
    AdcChannel12 [[maybe_unused]] = 12,
    AdcChannel13 [[maybe_unused]] = 13,
    AdcChannel14 [[maybe_unused]] = 14,
    AdcChannel15 [[maybe_unused]] = 15,
    AdcChannel16 [[maybe_unused]] = 16,
    AdcChannel17 [[maybe_unused]] = 17
  };

  /// @brief the size in bits of each reading. Readings are left aligned.
  enum class AdcResolution : uint16_t {
    Bits6 [[maybe_unused]] = 0U,
    Bits8  [[maybe_unused]] = 1U,
    Bits10  [[maybe_unused]] = 2U,
    Bits12  [[maybe_unused]] = 3U
  };

  /// @brief sample time for each reading before converting. Currently corresponds to STM32F334 and then mapped to the
  /// processors logically. THe sample time is nominally determined by the ADC clock.
  enum class AdcSamplingTime : uint16_t {
    SampleMin,
    Sample20Ns,
    Sample35Ns,
    Sample63Ns,
    Sample100Ns,
    Sample250Ns,
    Sample500Ns,
    Sample1Us,
    Sample2Us,
    Sample25Us,
    Sample3Us,
    Sample4Us,
    Sample5Us,
    Sample8Us,
    Sample17Us,
    SampleTemp,
    SampleMax,
  };

  /// @brief HOw the ADC uses the external trigger to start the next sample sequence
  enum class AdcTriggerMode : uint16_t {
    Software = 0U,
    HardwareRisingEdge [[maybe_unused]] = 1U,
    HardwareFallingEdge [[maybe_unused]] = 2U,
    HardwareBothEdges [[maybe_unused]] = 3U
  };

  /// @brief What source is used as the external trigger. May require expansion in future to accommodate additional
  /// source for additional processor types.
  enum class AdcExternalTrigger : uint16_t {
    Tim3Trgo [[maybe_unused]] = 4U,
    HrtimAdcTrg1 [[maybe_unused]] = 7U,
    HrtimAdcTrg3 [[maybe_unused]] = 8U,
    Tim1Trgo [[maybe_unused]] = 9U,
    Tim1Trgo2 [[maybe_unused]] = 10U,
  };

  /// @brief how the adc conversion of the programmed sequence is done.
  enum class AdcConversionMode : uint16_t {
    SingleConversion [[maybe_unused]] = 0u, /// Single reading
    SingleSequence [[maybe_unused]] = 1u,   /// Single sequence of reading as programmed
    SingleDma [[maybe_unused]] = 2u,        /// Single DMA buffer
    Continuous [[maybe_unused]] = 3u        /// Continuous non stop DMA.
  };

  using AdcTransferCompleteCb = Mem::Callback<8, void()>;

}

#endif
