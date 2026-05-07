## Day 1
- `++var`보다는 `var += 1`
- `return {}`을 항상 붙이고 시작 하기 (배열일 경우)
- `INT_MAX` 보다는 `std::numeric_limits<T>::max()`
- `if (b > a) a = b` 보다는 `std::max(a, b)`
- `stdlib`에 있는 함수명은 피하기 (min, max, data, count, size)