//
//  a2-soln.h
//  a2
//
//  Created by Dylan Peltier on 2024-01-25.
//

#ifndef a2_soln_h
#define a2_soln_h

#include <compare>
#include <istream>
#include <ostream>

enum class card_face {
    ace=1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king
};

enum class card_suit { clubs, spades, hearts, diamonds };

struct card {
    card_face face;
    card_suit suit;
    
    auto operator<=>(const card&) const=default;
};

std::ostream& operator<<(std::ostream& os, card_suit const suit);
std::ostream& operator<<(std::ostream& os, card_face const face);
std::ostream& operator<<(std::ostream& os, card const& c);
std::istream& operator>>(std::istream& is, card_suit& s);
std::istream& operator>>(std::istream& is, card_face& f);
std::istream& operator>>(std::istream& is, card& c);

std::ostream& operator<<(std::ostream& os, card_suit const suit) {
    switch (suit) {
        case card_suit::clubs:
            os << 'C';
            break;
        case card_suit::spades:
            os << 'S';
            break;
        case card_suit::diamonds:
            os << 'D';
            break;
        case card_suit::hearts:
            os << 'H';
            break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, card_face const face) {
    switch (face) {
        case card_face::ace:
            os << 'A';
            break;
        case card_face::jack:
            os << 'J';
            break;
        case card_face::queen:
            os << 'Q';
            break;
        case card_face::king:
            os << 'K';
            break;
        case card_face::two:
            os << '2';
            break;
        case card_face::three:
            os << '3';
            break;
        case card_face::four:
            os << '4';
            break;
        case card_face::five:
            os << '5';
            break;
        case card_face::six:
            os << '6';
            break;
        case card_face::seven:
            os << '7';
            break;
        case card_face::eight:
            os << '8';
            break;
        case card_face::nine:
            os << '9';
            break;
        case card_face::ten:
            os << "10";
            break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, card const& c) {
    os << c.face << c.suit;
    return os;
}

std::istream& operator>>(std::istream& is, card_suit& s) {
    char suit_char;
    is >> suit_char;
    
    switch (suit_char) {
        case 'C':
            s = card_suit::clubs;
            break;
        case 'S':
            s = card_suit::spades;
            break;
        case 'D':
            s = card_suit::diamonds;
            break;
        case 'H':
            s = card_suit::hearts;
            break;
        default:
            is.setstate(std::ios_base::failbit);
    }
    return is;
}

std::istream& operator>>(std::istream& is, card_face& f) {
    char face_char;
    is >> face_char;
    
    switch (face_char) {
        case 'A':
            f = card_face::ace;
            break;
        case 'J':
            f = card_face::jack;
            break;
        case 'Q':
            f = card_face::queen;
            break;
        case 'K':
            f = card_face::king;
            break;
        case '2':
            f = card_face::two;
            break;
        case '3':
            f = card_face::three;
            break;
        case '4':
            f = card_face::four;
            break;
        case '5':
            f = card_face::five;
            break;
        case '6':
            f = card_face::six;
            break;
        case '7':
            f = card_face::seven;
            break;
        case '8':
            f = card_face::eight;
            break;
        case '9':
            f = card_face::nine;
            break;
        case '1':
            char second_face_char;
            is >> second_face_char;
            
            if (second_face_char == '0') {
                f = card_face::ten;
            } else {
                is.setstate(std::ios_base::failbit);
            }
            break;
        default:
            is.setstate(std::ios_base::failbit);
    }
    return is;
}

std::istream& operator>>(std::istream& is, card& c) {
    is >> c.face >> c.suit;
    
    if (is.fail()) {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

#endif /* a2_soln_h */

