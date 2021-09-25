#include "interrupt_pin.hpp"
#include "internal/gpio.hpp"
#include "internal/pin.hpp"

#include <array>
#include <bit>
#include <cinttypes>
#include <libarmcortex/interrupt.hpp>
#include <libembeddedhal/context.hpp>
#include <libembeddedhal/gpio.hpp>

namespace embed::lpc40xx {
void interrupt_pin::interrupt_handler()
{
  unsigned int triggered_port = reg->IntStatus >> 2;
  unsigned int triggered_pin = 0;
  unsigned int status = 0;

  if (triggered_port == 0) {
    // To keep the number of handler functions to a minimum, this library does
    // not support seperate handlers for rising and falling edges. Therefore
    // it does not matter if a rising or falling edge triggered this
    // interrupt. OR both status together and clear them together below.
    status = reg->IO0IntStatR | reg->IO0IntStatF;

    // Clear interrupt flag on port 0. This is important as not doing this
    // will result in this interrupt being repeatedly called.
    xstd::bitmanip(reg->IO0IntClr).reset(triggered_pin);
  } else {
    // Same documentation as the port 0 case but with port 2 here.
    status = reg->IO2IntStatR | reg->IO2IntStatF;

    xstd::bitmanip(reg->IO2IntClr).reset(triggered_pin);
  }

  // Figure out which bit triggered this interrupt by checking the number of
  // zeros starting from the least significant bit. If there is 5 zeros,
  // then the next bit must be a 1 and thus, the pin that set off this
  // interrupt is pin 5. If there are 0 zeros, then the first bit must be
  // set to a 1 and thus pin 0 is what set off this interrupt. And so on for
  // all other bits.
  triggered_pin = std::countr_zero(status);

  handlers[triggered_port][triggered_pin]();
}

interrupt_pin::interrupt_pin(uint32_t p_port, uint32_t p_pin)
  : m_port(p_port)
  , m_pin(p_pin)
{
  if constexpr (!is_platform("lpc40")) {
    unittest_gpio();
    static lpc_gpio_interrupt_registers_t dummy{};
    reg = &dummy;
  }
}

bool interrupt_pin::driver_initialize()
{
  // Set pin as input
  xstd::bitmanip(gpio_port[m_port]->DIR).reset(m_pin);

  // Configure pin to use gpio function, use setting resistor and set the rest
  // to false.
  pin(m_port, m_pin)
    .function(0)
    .dac(false)
    .analog(false)
    .open_drain(false)
    .resistor(settings().resistor);

  // Enable interrupt for GPIOs and use interrupt handler as our handler.
  cortex_m::interrupt(gpio_irq).enable(interrupt_handler);

  return true;
}

bool interrupt_pin::level() const
{
  return xstd::bitmanip(gpio_port[m_port]->PIN).test(m_pin);
}

void interrupt_pin::attach_interrupt(std::function<void(void)> p_callback,
                                     trigger_edge p_trigger)
{
  handlers[m_port][m_pin] = p_callback;

  if (p_trigger == trigger_edge::both || p_trigger == trigger_edge::rising) {
    if (m_port == 0) {
      xstd::bitmanip(reg->IO0IntEnR).set(m_pin);
    } else {
      xstd::bitmanip(reg->IO2IntEnR).set(m_pin);
    }
  }
  if (p_trigger == trigger_edge::both || p_trigger == trigger_edge::falling) {
    if (m_port == 0) {
      xstd::bitmanip(reg->IO0IntEnF).set(m_pin);
    } else {
      xstd::bitmanip(reg->IO2IntEnF).set(m_pin);
    }
  }
}

void interrupt_pin::detach_interrupt()
{
  if (m_port == 0) {
    xstd::bitmanip(reg->IO0IntEnR).reset(m_pin);
    xstd::bitmanip(reg->IO0IntEnF).reset(m_pin);
  } else {
    xstd::bitmanip(reg->IO2IntEnR).reset(m_pin);
    xstd::bitmanip(reg->IO2IntEnF).reset(m_pin);
  }
}
}