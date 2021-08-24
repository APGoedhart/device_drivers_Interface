#ifndef DRIVERS_ADC_INCLUDE_DRIVERS_ADC_ADCDRIVER_HPP
#define DRIVERS_ADC_INCLUDE_DRIVERS_ADC_ADCDRIVER_HPP

#include <dataStructures/HeapArray.hpp>
#include <callbacks/Callback.hpp>
#include <drivers/adc/AdcTypes.hpp>

namespace Drivers {

/// Single Generic Reading for ADC
  using AdcReading = uint16_t;
  using AdcReadings = DataStructures::HeapArray<AdcReading>;

  /// @brief Driver for ADC that uses DMA to transfer readings into a defined buffer. The buffer needs to be word
  /// aligned to ensure correct DMA operation. Control of the buffer is returned on isTransferComplete call back
  /// notification .
  class AdcDriver  {
    public:

    AdcDriver()=default;
    virtual ~AdcDriver() = default;
    AdcDriver(const AdcDriver &) = delete;

    AdcDriver &operator=(const AdcDriver &) = delete;

    /// Initialise the ADC
    /// @param callback is the entity to notify when the conversion sequence has completed
    virtual void initialise(const AdcTransferCompleteCb &callback, AdcSamplingTime sampleTime)=0;

    /// Turn on or off both the voltage reference and temperature sensor.
    [[maybe_unused]] virtual void enableInternalSensors(bool enable)=0;

    /// Change the sampling time for the channels from the default
    [[maybe_unused]] virtual void setSamplingTime(AdcSamplingTime sampleTime)=0;

    /// Set the sequence that channels should be converted in the conversion sequence
    /// @param channel is the channel that should be converted
    /// @param position is the position of this channel in the sequence if supported.
    /// Channels should be assigned in incrementing position order. 0-n
    /// To reassign channels use a new set of assignments start at 0 and increment
    [[maybe_unused]] virtual void useChannel(AdcChannel channel, uint32_t position)=0;

    /// Starts a single sequence of conversions.
    [[maybe_unused]] virtual void startConversionSequence(AdcReadings &readings)=0;
  };
}

#endif
