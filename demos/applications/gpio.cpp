
#include <libarmcortex/dwt_counter.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <liblpc40xx/input_pin.hpp>
#include <liblpc40xx/output_pin.hpp>
#include <liblpc40xx/system_controller.hpp>

hal::status application()
{
  hal::cortex_m::dwt_counter clock(
    hal::lpc40xx::clock::get().get_frequency(hal::lpc40xx::peripheral::cpu));

  auto& button = HAL_CHECK((hal::lpc40xx::input_pin::get<0, 29>()));
  auto& led = HAL_CHECK((hal::lpc40xx::output_pin::get<1, 18>()));

  while (true) {
    // Checking level for the lpc40xx drivers NEVER generates an error so this
    // is fine.
    if (button.level().value()) {
      using namespace std::chrono_literals;
      HAL_CHECK(led.level(false));
      HAL_CHECK(hal::delay(clock, 200ms));
      HAL_CHECK(led.level(true));
      HAL_CHECK(hal::delay(clock, 200ms));
    }
  }
}