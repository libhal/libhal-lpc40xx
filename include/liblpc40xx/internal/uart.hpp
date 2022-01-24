#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <limits>

namespace embed::lpc40xx::internal {
struct uart_baud_t
{
  uint32_t divider;
  uint32_t numerator;
  uint32_t denominator;
};

struct fractional_divider_t
{
  int ratio;
  uint32_t numerator;
  uint32_t denominator;
};

constexpr std::array fractional_table{
  fractional_divider_t{ .ratio = 1000, .numerator = 0, .denominator = 1 },
  fractional_divider_t{ .ratio = 1250, .numerator = 1, .denominator = 4 },
  fractional_divider_t{ .ratio = 1500, .numerator = 1, .denominator = 2 },
  fractional_divider_t{ .ratio = 1750, .numerator = 3, .denominator = 4 },
  fractional_divider_t{ .ratio = 1067, .numerator = 1, .denominator = 15 },
  fractional_divider_t{ .ratio = 1267, .numerator = 4, .denominator = 15 },
  fractional_divider_t{ .ratio = 1533, .numerator = 8, .denominator = 15 },
  fractional_divider_t{ .ratio = 1769, .numerator = 10, .denominator = 13 },
  fractional_divider_t{ .ratio = 1071, .numerator = 1, .denominator = 14 },
  fractional_divider_t{ .ratio = 1273, .numerator = 3, .denominator = 11 },
  fractional_divider_t{ .ratio = 1538, .numerator = 7, .denominator = 13 },
  fractional_divider_t{ .ratio = 1778, .numerator = 7, .denominator = 9 },
  fractional_divider_t{ .ratio = 1077, .numerator = 1, .denominator = 13 },
  fractional_divider_t{ .ratio = 1286, .numerator = 2, .denominator = 7 },
  fractional_divider_t{ .ratio = 1545, .numerator = 6, .denominator = 11 },
  fractional_divider_t{ .ratio = 1786, .numerator = 11, .denominator = 14 },
  fractional_divider_t{ .ratio = 1083, .numerator = 1, .denominator = 12 },
  fractional_divider_t{ .ratio = 1300, .numerator = 3, .denominator = 10 },
  fractional_divider_t{ .ratio = 1556, .numerator = 5, .denominator = 9 },
  fractional_divider_t{ .ratio = 1800, .numerator = 4, .denominator = 5 },
  fractional_divider_t{ .ratio = 1091, .numerator = 1, .denominator = 11 },
  fractional_divider_t{ .ratio = 1308, .numerator = 4, .denominator = 13 },
  fractional_divider_t{ .ratio = 1571, .numerator = 4, .denominator = 7 },
  fractional_divider_t{ .ratio = 1818, .numerator = 9, .denominator = 11 },
  fractional_divider_t{ .ratio = 1100, .numerator = 1, .denominator = 10 },
  fractional_divider_t{ .ratio = 1333, .numerator = 1, .denominator = 3 },
  fractional_divider_t{ .ratio = 1583, .numerator = 7, .denominator = 12 },
  fractional_divider_t{ .ratio = 1833, .numerator = 5, .denominator = 6 },
  fractional_divider_t{ .ratio = 1111, .numerator = 1, .denominator = 9 },
  fractional_divider_t{ .ratio = 1357, .numerator = 5, .denominator = 14 },
  fractional_divider_t{ .ratio = 1600, .numerator = 3, .denominator = 5 },
  fractional_divider_t{ .ratio = 1846, .numerator = 11, .denominator = 13 },
  fractional_divider_t{ .ratio = 1125, .numerator = 1, .denominator = 8 },
  fractional_divider_t{ .ratio = 1364, .numerator = 4, .denominator = 11 },
  fractional_divider_t{ .ratio = 1615, .numerator = 8, .denominator = 13 },
  fractional_divider_t{ .ratio = 1857, .numerator = 6, .denominator = 7 },
  fractional_divider_t{ .ratio = 1133, .numerator = 2, .denominator = 15 },
  fractional_divider_t{ .ratio = 1375, .numerator = 3, .denominator = 8 },
  fractional_divider_t{ .ratio = 1625, .numerator = 5, .denominator = 8 },
  fractional_divider_t{ .ratio = 1867, .numerator = 13, .denominator = 15 },
  fractional_divider_t{ .ratio = 1143, .numerator = 1, .denominator = 7 },
  fractional_divider_t{ .ratio = 1385, .numerator = 5, .denominator = 13 },
  fractional_divider_t{ .ratio = 1636, .numerator = 7, .denominator = 11 },
  fractional_divider_t{ .ratio = 1875, .numerator = 7, .denominator = 8 },
  fractional_divider_t{ .ratio = 1154, .numerator = 2, .denominator = 13 },
  fractional_divider_t{ .ratio = 1400, .numerator = 2, .denominator = 5 },
  fractional_divider_t{ .ratio = 1643, .numerator = 9, .denominator = 14 },
  fractional_divider_t{ .ratio = 1889, .numerator = 8, .denominator = 9 },
  fractional_divider_t{ .ratio = 1167, .numerator = 1, .denominator = 6 },
  fractional_divider_t{ .ratio = 1417, .numerator = 5, .denominator = 12 },
  fractional_divider_t{ .ratio = 1667, .numerator = 2, .denominator = 3 },
  fractional_divider_t{ .ratio = 1900, .numerator = 9, .denominator = 10 },
  fractional_divider_t{ .ratio = 1182, .numerator = 2, .denominator = 11 },
  fractional_divider_t{ .ratio = 1429, .numerator = 3, .denominator = 7 },
  fractional_divider_t{ .ratio = 1692, .numerator = 9, .denominator = 13 },
  fractional_divider_t{ .ratio = 1909, .numerator = 10, .denominator = 11 },
  fractional_divider_t{ .ratio = 1200, .numerator = 1, .denominator = 5 },
  fractional_divider_t{ .ratio = 1444, .numerator = 4, .denominator = 9 },
  fractional_divider_t{ .ratio = 1700, .numerator = 7, .denominator = 10 },
  fractional_divider_t{ .ratio = 1917, .numerator = 11, .denominator = 12 },
  fractional_divider_t{ .ratio = 1214, .numerator = 3, .denominator = 14 },
  fractional_divider_t{ .ratio = 1455, .numerator = 5, .denominator = 11 },
  fractional_divider_t{ .ratio = 1714, .numerator = 5, .denominator = 7 },
  fractional_divider_t{ .ratio = 1923, .numerator = 12, .denominator = 13 },
  fractional_divider_t{ .ratio = 1222, .numerator = 2, .denominator = 9 },
  fractional_divider_t{ .ratio = 1462, .numerator = 6, .denominator = 13 },
  fractional_divider_t{ .ratio = 1727, .numerator = 8, .denominator = 11 },
  fractional_divider_t{ .ratio = 1929, .numerator = 13, .denominator = 14 },
  fractional_divider_t{ .ratio = 1231, .numerator = 3, .denominator = 13 },
  fractional_divider_t{ .ratio = 1467, .numerator = 7, .denominator = 15 },
  fractional_divider_t{ .ratio = 1733, .numerator = 11, .denominator = 15 },
  fractional_divider_t{ .ratio = 1933, .numerator = 14, .denominator = 15 },
};

constexpr fractional_divider_t closest_fractional(int32_t multiplier)
{
  fractional_divider_t result = fractional_table[0];
  auto difference = std::numeric_limits<int32_t>::max();

  for (auto const& fraction : fractional_table) {
    auto new_difference = labs(multiplier - fraction.ratio);
    if (new_difference < difference) {
      result = fraction;
      difference = new_difference;
    }
  }

  return result;
}

constexpr uart_baud_t calculate_baud(uint32_t baud_rate, int64_t frequency_hz)
{
  // The number of samples per UART frame bit.
  // This is used as a multiplier for the baudrate.
  constexpr uint32_t samples_per_bit_rate = 16;
  constexpr uint64_t thousands = 1000;

  // Hold the result return value.
  uart_baud_t result{};

  const uint64_t frequency_1000 = frequency_hz * thousands;
  const uint32_t sample_rate = baud_rate * samples_per_bit_rate;

  // Compute the integer divider for the baud rate
  const uint32_t integer_divider = (frequency_hz / sample_rate);

  // Computer the integer divider for the baud rate except multiplied by 1000
  // in order to get 3 additional decimal places.
  const auto divider_1000 = static_cast<uint32_t>(frequency_1000 / sample_rate);

  // Save divider to result
  result.divider = integer_divider;

  // Check if the integer divider is not zero because not doing that will cause
  // a division error. Also note that an integer divider of 0 represents a
  // failure.
  if (integer_divider != 0) {
    const auto multiplier_ratio = divider_1000 / integer_divider;
    const fractional_divider_t fraction = closest_fractional(multiplier_ratio);
    result.numerator = fraction.numerator;
    result.denominator = fraction.denominator;
  }

  return result;
}
} // namespace embed::lpc40xx::internal