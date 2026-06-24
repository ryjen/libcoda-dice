
#include "dice.test.h"

#include <limits>
#include <string>

#include "dice.h"
#include <bandit/bandit.h>

using namespace bandit;

using namespace coda;

using namespace snowhouse;

dice_test_engine::dice_test_engine() : values_(), currentValue_(0) {}

dice_test_engine::dice_test_engine(initializer_list<die::value_type> value)
    : values_(value), currentValue_(0) {}

dice_test_engine::dice_test_engine(const dice_test_engine &copy)
    : values_(copy.values_.size()), currentValue_(copy.currentValue_) {
  for (auto &d : copy.values_)
    values_.push_back(d);
}

dice_test_engine &dice_test_engine::operator=(const dice_test_engine &rhs) {
  if (this != &rhs) {
    values_ = rhs.values_;
    currentValue_ = rhs.currentValue_;
  }

  return *this;
}

dice_test_engine::~dice_test_engine() {}

die::value_type dice_test_engine::generate(die::value_type from,
                                           die::value_type to) {
  if (values_.size() == 0)
    return 0;

  if (currentValue_ >= values_.size()) {
    currentValue_ = 0;
  }

  return values_[currentValue_++];
}

void dice_test_engine::set_next_roll(initializer_list<die::value_type> items) {
  values_ = items;
  currentValue_ = 0;
}

go_bandit([]() {
  describe("a die", []() {
    it("has a default constructor", []() {
      die d;

      Assert::That(d.sides(), Equals(die::DEFAULT_SIDES));
    });

    it("can be constructed with sides", []() {
      die d(100);

      Assert::That(d.sides(), Equals(100));
    });

    it("throws invalid_argument for zero sides", []() {
      AssertThrows(invalid_argument, die(0));
    });

    it("can be copied", []() {
      die d(10);

      die d2 = d;

      Assert::That(d2.sides(), Equals(10));
    });

    it("can be rolled", []() {
      die d(10);

      for (int i = 0; i < 10; i++) {
        Assert::That(d.sides(), IsGreaterThan(0));
        Assert::That(d.sides(), IsLessThan(11));
      }
    });

    it("has sides", []() {
      die d(7);

      Assert::That(d.sides(), Equals(7));

      d.sides(25);

      Assert::That(d.sides(), Equals(25));
    });
  });

  describe("some dice", []() {
    it("can be constructed with the number of die", []() {
      dice d(10);

      Assert::That(d.size(), Equals(10));
    });

    it("can be constructed with the number of die and sides per die", []() {
      dice dice(10, 10);

      Assert::That(dice.size(), Equals(10));

      for (die &d : dice) {
        Assert::That(d.sides(), Equals(10));
      }
    });

    it("has a size", []() {
      dice d(10);

      Assert::That(d.size(), Equals(10));
    });

    it("has a bonus value", []() {
      dice d(2);

      d.bonus(23);

      Assert::That(d.bonus(), Equals(23));
    });

    it("doesn't underflow on bonus", []() {
      dice d(2);

      d.bonus(-100);

      Assert::That(d.roll(), Equals(0));
    });

    it("doesn't overflow on bonus", []() {
      dice_test_engine engine;

      dice d(2, 5, &engine);

      d.bonus(200);

      engine.set_next_roll({numeric_limits<die::value_type>::max() - 50});

      Assert::That(d.roll(), Equals(numeric_limits<die::value_type>::max()));
    });

    it("can be converted to a string", []() {
      dice d(10, 20);

      Assert::That(d.to_string(), Equals("10d20"));

      d.bonus(5);

      Assert::That(d.to_string(), Equals("10d20+5"));
    });
  });
});
