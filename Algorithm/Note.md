## Day 1
- `var += 1`보다는 `++var`
- `return {}`을 항상 붙이고 시작 하기 (배열일 경우)
- `INT_MAX` 보다는 `std::numeric_limits<T>::max()`
- `if (b > a) a = b` 보다는 `std::max(a, b)`
- `stdlib`에 있는 함수명은 피하기 (min, max, data, count, size)

## Day 2
- unordered_set<T>::count(T); T가 set 안에 얼마나 있는지로 set안에 해당 인스턴스가 있는지 판별 가능
- 자료형이 담당해주지 못 하는 부분은 따로 다른 도구 이용
