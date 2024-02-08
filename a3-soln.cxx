#include <algorithm>  // e.g., for any_of, none_of, count_if, sample
#include <iostream>
#include <istream>
#include <iterator>   // e.g., for input_iterator, input_iterator_tag
#include <optional>
#include <ostream>
#include <random>     // e.g., for default_random_engine, random_device
#include <ranges>     // e.g., for ranges::range
#include <vector>

#include "a2-soln.hxx" // as required in this assignment
#include "a2-soln.hxx" // as required in this assignment

struct all_card_faces_begin_t final {};
constexpr all_card_faces_begin_t all_card_faces_begin{};

class all_card_faces_iterator {
public:
    using value_type = card_face const;
    using reference = value_type&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    all_card_faces_iterator() = default;

    all_card_faces_iterator(const all_card_faces_iterator&) = default;

    all_card_faces_iterator& operator=(const all_card_faces_iterator&) = default;

    all_card_faces_iterator(all_card_faces_begin_t) : f_(card_face::ace) {}

    std::strong_ordering operator<=>(const all_card_faces_iterator& other) const = default;

    reference operator*() const { return *f_; }

    all_card_faces_iterator operator++(int) {
        all_card_faces_iterator tmp(*this);
        this->operator++();
        return tmp;
    }

    all_card_faces_iterator& operator++() {
        if (f_.has_value()) {
            if (f_ == card_face::king) {
                f_ = std::nullopt;
            } else {
                using int_type = std::underlying_type_t<card_face>;
                int_type current_value = static_cast<int_type>(*f_);
                current_value = current_value + 1;
                f_ = static_cast<card_face>(current_value);
            }
        }

        return *this;
    }

private:
    std::optional<card_face> f_;
};

static_assert(std::input_iterator<all_card_faces_iterator>);

class all_card_faces {
public:
    all_card_faces_iterator begin() const {
        return all_card_faces_iterator{all_card_faces_begin};
    }

    all_card_faces_iterator end() const {
        return all_card_faces_iterator{};
    }
};

static_assert(std::ranges::range<all_card_faces>);

struct all_card_suits_begin_t final {};
constexpr all_card_suits_begin_t all_card_suits_begin{};

class all_card_suits_iterator {
public:
    using value_type = card_suit const;
    using reference = value_type&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    all_card_suits_iterator() = default;

    all_card_suits_iterator(const all_card_suits_iterator&) = default;

    all_card_suits_iterator& operator=(const all_card_suits_iterator&) = default;

    all_card_suits_iterator(all_card_suits_begin_t) : s_(card_suit::clubs) {}

    std::strong_ordering operator<=>(const all_card_suits_iterator& other) const = default;

    reference operator*() const { return *s_; }

    all_card_suits_iterator operator++(int) {
        all_card_suits_iterator tmp(*this);
        this->operator++();
        return tmp;
    }

    all_card_suits_iterator& operator++() {
        if (s_.has_value()) {
            if (s_ == card_suit::diamonds) {
                s_ = std::nullopt;
            } else {
                using int_type = std::underlying_type_t<card_suit>;
                int_type current_value = static_cast<int_type>(*s_);
                current_value = current_value + 1;
                s_ = static_cast<card_suit>(current_value);
            }
        }

        return *this;
    }

private:
    std::optional<card_suit> s_;
};

static_assert(std::input_iterator<all_card_suits_iterator>);

class all_card_suits {
public:
    all_card_suits_iterator begin() const {
        return all_card_suits_iterator{all_card_suits_begin};
    }

    all_card_suits_iterator end() const {
        return all_card_suits_iterator{};
    }
};

static_assert(std::ranges::range<all_card_suits>);

using cards = std::vector<card>;

cards generate_full_deck() {
    cards retval;
    for (card_face f : all_card_faces{})
        for (card_suit s : all_card_suits{})
            retval.push_back(card{ f, s });
    return retval;
}

cards generate_different_deck() {
    cards retval;
    for (card_face f : all_card_faces{})
        for (card_suit s : all_card_suits{})
            if (f != card_face::two &&
                f != card_face::three &&
                f != card_face::four &&
                f != card_face::five &&
                f != card_face::six) {
                retval.push_back(card { f, s });
            }
    return retval;
}

std::ostream& operator<<(std::ostream& os, cards const& cs) {
	for (auto const& c : cs) {
		os << c.face << ' ' << c.suit;
	}
	return os;
}

bool is_red(card const& c) {
	if (c.suit == card_suit::diamonds || c.suit == card_suit::hearts) {
		return true;
	} else {
		return false;
	}
}

bool is_club(card const& c) {
	if (c.suit != card_suit::clubs) {
		return false;
	} else {
		return true;
	}
}

cards select_n(cards const& cs, std::size_t n) {
	static std::default_random_engine rand_eng{std::random_device{}()};
	cards retval;
	std::sample(cs.begin(), cs.end(), std::back_inserter(retval), n, rand_eng);
	return retval;
}

std::size_t aces_low_total(cards const& cs) {
   return std::accumulate(cs.begin(), cs.end(), 0U, [](std::size_t partial_sum, card const& c) {
        int value = static_cast<int>(c.face);
        if (value >= 10) {
            return partial_sum + 10;
        } else {
            return partial_sum + value;
        }
    });
}

std::size_t aces_high_total(cards const& cs) {
    return std::accumulate(cs.begin(), cs.end(), 0U, [](std::size_t partial_sum, card const& c) {
         int value = static_cast<int>(c.face);
         if (value >= 10 || value == 1) {
             return partial_sum + 10;
         } else {
             return partial_sum + value;
         }
     });
}
std::ostream& info(std::ostream& os, cards const& cs) {
    os << "cards: ";
    for (auto const& c : cs) {
        os << c.face << c.suit << " ";
    }
    os << "\n";
    os << " # cards: " << cs.size() << "\n";
    os << " # red cards: " << std::count_if(cs.begin(), cs.end(), is_red) << "\n";
    os << " # club suit cards: " << std::count_if(cs.begin(), cs.end(), is_club) << "\n";
    os << " # of 10-on-face cards: " << std::count_if(cs.begin(), cs.end(), [](card const& c) {
        if (c.face == card_face::ten) {
            return true;
        } else {
            return false;
        }
    }) << "\n";
    os << " # of 3-on-face cards: " << std::count_if(cs.begin(), cs.end(), [](card const& c) {
        if (c.face == card_face::three) {
            return true;
        } else {
            return false;
        }
    }) << "\n\n";

    bool found_hand_with_ace = false;
    bool found_hand_without_ace = false;

    while (found_hand_with_ace != true && found_hand_without_ace != true) {
        auto hand = select_n(cs, 7);
        os << " sample hand: ";
        for (auto const& c : hand) {
            os << c.face << c.suit << " ";
        }
	os << "\n";
	os << "  total (A == 1, JQK == 10): " << aces_low_total(hand) << "\n";
        os << "  total (AJQK == 10): " << aces_high_total(hand) << "\n\n";

        found_hand_with_ace = found_hand_with_ace || std::any_of(hand.begin(), hand.end(), [](card const& c) {
            return c.face == card_face::ace;
        });

        found_hand_without_ace = found_hand_without_ace || std::any_of(hand.begin(), hand.end(), [](card const& c) {
            return c.face == card_face::ace;
        });
    }
    return os;
}

int main()
{
  using namespace std;

  info(cout, generate_full_deck());
  info(cout, generate_different_deck());
}
