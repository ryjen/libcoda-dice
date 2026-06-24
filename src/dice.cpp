
#include "dice.h"
#include <cassert>
#include <functional>
#include <random>

namespace coda {
  // #######################################################################################################
  // die
  // #######################################################################################################

  // randomness for dice rolls
  static detail::default_engine default_die_engine = detail::default_engine();

  const die::value_type die::DEFAULT_SIDES;

  die::engine *const die::default_engine = &default_die_engine;

  die::value_type detail::default_engine::generate(die::value_type from,
                                                   die::value_type to) {
    static std::default_random_engine random_engine(time(0));

    uniform_int_distribution<die::value_type> distribution(from, to);

    return distribution(random_engine);
  }

  die::die(const unsigned int sides, die::engine *const engine)
      : engine_(engine), value_(0) {
    if (sides == 0) {
      throw invalid_argument("dice must have one or more sides.");
    }

    sides_ = sides;
  }

  die::die(const die &other)
      : engine_(other.engine_), sides_(other.sides_), value_(other.value_) {}

  die::die(die &&other)
      : engine_(std::move(other.engine_)), sides_(other.sides_),
        value_(other.value_) {}

  die &die::operator=(const die &other) {
    engine_ = other.engine_;
    sides_ = other.sides_;
    value_ = other.value_;

    return *this;
  }

  die &die::operator=(die &&other) {
    engine_ = std::move(other.engine_);
    sides_ = other.sides_;
    value_ = other.value_;

    return *this;
  }

  die::~die() {
    // nothing to do
  }

  bool die::operator==(const die &rhs) const noexcept {
    return value_ == rhs.value_;
  }

  bool die::operator!=(const die &rhs) const noexcept {
    return !operator==(rhs);
  }

  die::operator value_type() const noexcept { return value_; }

  /*
   * returns the number of sides on the die
   */
  unsigned int die::sides() const noexcept { return sides_; }

  /*
   * sets the number of sides on the die
   */
  void die::sides(const unsigned int value) noexcept { sides_ = value; }

  die::value_type die::value() const noexcept { return value_; }

  // returns one of the sides on the die (random)
  die::value_type die::roll() {
    assert(engine_ != 0);

    value_ = engine_->generate(1, sides_);

    return value_;
  }

  // #######################################################################################################
  // dice
  // #######################################################################################################

  // creates x dice with y sides
  dice::dice(const unsigned int count, const unsigned int sides,
             die::engine *const engine)
      : bonus_(0), dice_() {
    for (size_t i = 0; i < count; i++)
      dice_.push_back(die(sides, engine));
  }

  // copy constructor
  dice::dice(const dice &other) noexcept
      : bonus_(other.bonus_), dice_(other.dice_) {}

  // move constructor
  dice::dice(dice &&other) noexcept
      : bonus_(other.bonus_), dice_(std::move(other.dice_)) {}

  dice &dice::operator=(const dice &other) noexcept {
    bonus_ = other.bonus_;
    dice_ = other.dice_;

    return *this;
  }

  dice &dice::operator=(dice &&other) noexcept {
    bonus_ = other.bonus_;
    dice_ = std::move(other.dice_);

    return *this;
  }

  // deconstructor
  dice::~dice() noexcept {}

  // iterator methods
  dice::iterator dice::begin() noexcept { return dice_.begin(); }

  dice::const_iterator dice::begin() const noexcept { return dice_.begin(); }

  // const iterator methods
  const dice::const_iterator dice::cbegin() const noexcept {
    return dice_.cbegin();
  }

  dice::iterator dice::end() noexcept { return dice_.end(); }

  dice::const_iterator dice::end() const noexcept { return dice_.end(); }

  const dice::const_iterator dice::cend() const noexcept {
    return dice_.cend();
  }

  unsigned int dice::size() const noexcept { return dice_.size(); }

  /*
   * returns the bonus value
   */
  int dice::bonus() const noexcept { return bonus_; }

  /*
   * sets the bonus value
   */
  void dice::bonus(const int value) noexcept { bonus_ = value; }

  // a string representation of the dice ex. 5d20
  const string dice::to_string() const {
    stringstream buf;

    size_t size = dice_.size();

    buf << size;

    if (size > 0) {
      buf << "d" << dice_.begin()->sides();
    }

    if (bonus_ > 0) {
      buf << "+" << bonus_;
    }
    return buf.str();
  }

  //! return the total of rolling all dice
  /*!
   * @param   selector    determins if a die should be rolled or use it's
   * current value
   */
  die::value_type
  dice::roll(std::function<bool(size_t index, const die &d)> selector) {
    die::value_type value = 0;

    for (size_t i = 0; i < dice_.size(); i++) {
      auto &d = dice_[i];

      die::value_type roll;

      if (selector == nullptr || selector(i, d)) {
        roll = d.roll();
      } else {
        roll = d.value();
      }

      value += roll; // sum the total
    }

    /* return value has the bonus */
    int b = bonus();

    if (b < 0) {
      // avoid unsigned underflow
      if (static_cast<int>(value) + b >= 0)
        return value + b;
      else
        return 0;
    } else {
      // avoid unsigned overflow
      if (numeric_limits<die::value_type>::max() - value >=
          static_cast<die::value_type>(b))
        return value + b; // add the bonus
      else
        return numeric_limits<die::value_type>::max();
    }
  }

  die &dice::operator[](size_t n) { return dice_[n]; }

  const die &dice::operator[](size_t n) const { return dice_[n]; }

  ostream &operator<<(ostream &out, const dice &dice) {
    out << dice.to_string();
    return out;
  }
} // namespace coda
