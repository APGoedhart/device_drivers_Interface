#ifndef DRIVERS_INTERFACE_GPIO_INCLUDE_DRIVERS_GPIO_GPIOTYPES_HPP
#define DRIVERS_INTERFACE_GPIO_INCLUDE_DRIVERS_GPIO_GPIOTYPES_HPP

#include <cstdint>
#include <dataTypes/EnumValue.hpp>
#include <typeConversion/ConvertTypes.hpp>

namespace Drivers {
  enum class GpioPort : uint8_t {
    GpioA [[maybe_unused]] = 0U,
    GpioB [[maybe_unused]] = 1U,
    GpioC [[maybe_unused]] = 2U,
    GpioD [[maybe_unused]] = 3U,
    GpioE [[maybe_unused]] = 4U,
    GpioF [[maybe_unused]] = 5U,
    GpioG [[maybe_unused]] = 6U,
    Invalid [[maybe_unused]] = 7U,
  };

  enum class GpioPin : uint8_t {
    Pin0 [[maybe_unused]] = 0U,
    Pin1 [[maybe_unused]] = 1U,
    Pin2 [[maybe_unused]] = 2U,
    Pin3 [[maybe_unused]] = 3U,
    Pin4 [[maybe_unused]] = 4U,
    Pin5 [[maybe_unused]] = 5U,
    Pin6 [[maybe_unused]] = 6U,
    Pin7 [[maybe_unused]] = 7U,
    Pin8 [[maybe_unused]] = 8U,
    Pin9 [[maybe_unused]] = 9U,
    Pin10 [[maybe_unused]] = 10U,
    Pin11 [[maybe_unused]] = 11U,
    Pin12 [[maybe_unused]] = 12U,
    Pin13 [[maybe_unused]] = 13U,
    Pin14 [[maybe_unused]] = 14U,
    Pin15 [[maybe_unused]] = 15U
  };


  /// \class GpioMode enum

  enum class GpioMode : uint32_t {
    Input = 0U,
    Output = 1U,
    Peripheral = 2U,
    Analog [[maybe_unused]] = 3U
  };


  /// \class GpioState enum
  enum class GpioState : uint32_t {
    Low = 0U,
    High = 1U,
    Invalid = 2U
  };


  /// \class GpioDrive enum
  enum class GpioDrive : uint32_t {
    PushPull = 0U,
    OpenDrain [[maybe_unused]] = 1U
  };


  /// \class GpioSpeed enum
  enum class GpioSpeed : uint32_t {
    Low = 0U,
    Medium [[maybe_unused]] = 1U,
    High = 2U
  };


  /// \class GpioResistor enum

  enum class GpioResistor : uint32_t {
    None = 0U,
    PullUp [[maybe_unused]] = 1U,
    PullDown = 2U
  };

  /// \class GpioAlternateFunction enum
  enum class GpioAlternateFunction : uint32_t {
    Af0 [[maybe_unused]] = 0x00U,
    Af1 [[maybe_unused]] = 0x01U,
    Af2 [[maybe_unused]] = 0x02U,
    Af3 [[maybe_unused]] = 0x03U,
    Af4 [[maybe_unused]] = 0x04U,
    Af7 [[maybe_unused]] = 0x07U,
    Af12 [[maybe_unused]] = 0x0CU,
    Af13 [[maybe_unused]] = 0x0DU,
    AfNone = 0xF4
  };

  /// #brief  Holds the port and pin designator for a single pin.
  class PortPin {
    public:
    constexpr PortPin() :
        ioPin(invalid) {
    }

    constexpr PortPin(const GpioPort port, const GpioPin pin) :
        ioPin(static_cast<uint8_t>((static_cast<uint32_t>(port) << 4) | static_cast<uint32_t>(pin))) {
    }

    constexpr explicit PortPin(const uint8_t packed) : ioPin(packed) {
    }

    [[nodiscard]] constexpr uint8_t getPacked() const {
      return ioPin;
    }

    /// Return true if the pin is a valid pin

    [[nodiscard]] constexpr bool isValid() const {
      return (ioPin != invalid);
    }

    [[nodiscard]] constexpr uint32_t getPin() const {
      return ioPin & 0x0FU;
    }


    [[nodiscard]] constexpr uint32_t getPort() const {
      return static_cast<uint32_t>((ioPin >> 4U)) & 0x0FU;
    }

    constexpr bool operator==(const PortPin &rhs) const {
      return (ioPin == rhs.ioPin);
    }

    private:
    static constexpr uint8_t invalid = 0xFFU;
    uint8_t ioPin;
  };


  /// Pin configuration for logical pins
  class PinConfiguration {

    public:
    explicit constexpr PinConfiguration(const uint32_t conf) : config(conf) {}

    constexpr PinConfiguration(const PortPin p, const GpioAlternateFunction af, const GpioResistor r, const GpioDrive d) :
        config(pack(p, af, r, d)) {}

    constexpr PinConfiguration(const PortPin p, const GpioResistor r, const GpioDrive d) :
        config(pack(p, GpioAlternateFunction::AfNone, r, d)) {}

    constexpr PinConfiguration(const PortPin p, const GpioAlternateFunction af, const GpioResistor r) :
        config(pack(p, af, r, GpioDrive::PushPull)) {}

    constexpr PinConfiguration( const PortPin p, const GpioResistor r) :
        config(pack(p, GpioAlternateFunction::AfNone, r, GpioDrive::PushPull)) {}

    constexpr PinConfiguration(const PortPin p, const GpioAlternateFunction af) :
        config(pack(p, af, GpioResistor::PullDown, GpioDrive::PushPull)) {}

    constexpr  explicit PinConfiguration(const PortPin p) :
        config(pack(p, GpioAlternateFunction::AfNone, GpioResistor::PullDown, GpioDrive::PushPull)) {}

    constexpr PinConfiguration() :
        config(pack(PortPin(), GpioAlternateFunction::AfNone, GpioResistor::PullDown, GpioDrive::PushPull)) {}


   [[nodiscard]] constexpr PortPin getPortPin() const {
      return PortPin(static_cast<uint8_t>(config & 0xFF));
    }

    [[nodiscard]] constexpr bool isValid() const {
      return getPortPin().isValid();
    }

    [[nodiscard]] constexpr GpioAlternateFunction getAltF() const {
      return static_cast<GpioAlternateFunction>((config >> 8) & 0xFF);
    }

    [[nodiscard]] constexpr GpioResistor getResistor() const {
      return static_cast<GpioResistor>((config >> 16) & 0xFF);
    }

    [[nodiscard]] constexpr GpioDrive getDrive() const {
      return static_cast<GpioDrive>((config >> 24) & 0xFF);
    }

    constexpr explicit operator uint32_t() const {
      return config;
    }

    private:
    uint32_t config;


    constexpr static uint32_t pack(const PortPin p, const GpioAlternateFunction af, const GpioResistor r, const GpioDrive d) {
      return p.getPacked() | (asInt(af) << 8) | (asInt(r) << 16) | (asInt(d) << 24);
    }
  };


}

#endif
