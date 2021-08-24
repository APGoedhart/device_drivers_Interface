#ifndef DRIVERS_DMA_INCLUDE_DRIVERS_DMA_DMACHANNELDRIVER_HPP
#define DRIVERS_DMA_INCLUDE_DRIVERS_DMA_DMACHANNELDRIVER_HPP

#include <drivers/dma/DmaTypes.hpp>

namespace Drivers {
  ///@brief managed a single DMA channel for another peripheral  / driver.
  class DmaChannelDriver  {
    public:
    explicit DmaChannelDriver()= default;
    virtual ~DmaChannelDriver() = default;
    DmaChannelDriver(const DmaChannelDriver&) = delete;
    DmaChannelDriver &operator=(const DmaChannelDriver&) = delete;

    ///Initialise the DMA channel
    ///\param notify is an object that will be called when the transfer completes
    ///\param newDmaPriority The priority of this DMA transfer relative to the other DMA transfers
    virtual void initialise(const TransferCompleteCb & newNotify, DmaPriority newDmaPriority,
                            DataWidth width, TransferDirection direction) const = 0;

      
    ///Sets up a transfer from a peripheral to memory of the other way round depending on the channel
    ///\param data is a buffer where the data will be read from /written to
    ///\param peripheral is the address of the peripherals register
    ///\param numberOfBlocks is the number of blocks to transfer
    ///\param autoReloadMode indicates whether the DMA should reload after the transfer
    template <typename DATA, typename PERIPHERAL>
    void setupTransfer(DATA *data, volatile PERIPHERAL *peripheral, uint16_t numberOfBytes,
                       AutoReload autoReloadMode) const;

    ///Enable the half transfer interrupt
    virtual void enableHalfTransferInterrupt() const =0 ;

    ///Start the dma transfer to or from the peripheral
    virtual void startTransfer() const =0 ;

    ///Get the number of blocks remaining in the transfer
    ///\return the number of blocks remaining in the current transfer The block size is dependant on the the Dma width
    [[nodiscard]] virtual uint32_t getBlocksRemaining() const =0;

    ///Get the DMA channel that this driver wraps
    ///\return the DMA channel
    [[nodiscard]] virtual DmaChannel getChannel() const =0;

    ///Return true if the DMA channel is currently enabled.
    [[nodiscard]] virtual bool isEnabled() const =0;

    ///Terminate the current DMA transfer gracefully.
    virtual void terminateTransfer() const =0;

    protected:
    ///@brief type erasure method for template method
    virtual void setupTransferImpl(void *data, volatile void *peripheral, uint16_t
                                   numberOfBytes, AutoReload autoReloadMode) const=0;

  };

  /// @brief This method provides type erasure for the Driver. Conversion to voi is always defined.
  ///        The hardware peripheral takes a raw pointer.
  ///
  template <typename DATA, typename PERIPHERAL>
  void DmaChannelDriver::setupTransfer(DATA *data, volatile PERIPHERAL *peripheral, uint16_t numberOfBytes, AutoReload autoReloadMode) const{
    static_assert(std::is_integral_v<DATA>, "data pointers for transfer should be to intrinsic types");
    static_assert(std::is_integral_v<PERIPHERAL>, "peripheral pointers should be to intrinsic types");
    setupTransferImpl(data, peripheral, numberOfBytes, autoReloadMode);
  }

}

#endif
