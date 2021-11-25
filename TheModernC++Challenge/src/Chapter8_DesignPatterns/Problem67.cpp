#include "Chapter8_DesignPatterns.h"

#include <algorithm>  // all_of, any_of
#include <cctype>  // isalpha, isdigit, islower, isupper
#include <iostream>  // cout
#include <optional>
#include <string>
#include <string_view>


using validate_error_message = std::string;
using validate_return_type = std::optional<validate_error_message>;


// This solution uses the Chain of Responsibility pattern
//
// The PasswordStrengthValidator base class:
//   - specifies a 'validate' interface,
//   - holds a pointer to the next validator in the chain, offering a setter for it, and
//   - lets validators to continue the validation process through a 'validate_with_next' method
//
// The different concrete classes:
//   - implement the validate interface, and
//   - whether they return an error or they return control to the base class to continue with the validation
//
class PasswordStrengthValidator
{
public:
    virtual validate_return_type validate(std::string_view pw) const noexcept = 0;

    void set_next(PasswordStrengthValidator* next) noexcept { next_ = next; }
protected:
    PasswordStrengthValidator* next_{ nullptr };

    [[nodiscard]] validate_return_type validate_with_next(std::string_view pw) const noexcept {
        return (next_ ? next_->validate(pw) : validate_return_type{});
    }
};


class MinimumLengthValidator : public PasswordStrengthValidator
{
public:
    MinimumLengthValidator() = default;
    explicit MinimumLengthValidator(size_t length) : length_{ length } {}

    [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
        if (pw.size() < length_) { return std::string{"password length has to be at least "} + std::to_string(length_); }
        else { return validate_with_next(pw); };
    }
private:
    size_t length_{8};
};


template <typename Predicate>
class ContainsValidator : public PasswordStrengthValidator
{
public:
    ContainsValidator() = delete;
    explicit ContainsValidator(Predicate pred, std::string_view error_message) : pred_{ pred }, error_message_{ error_message } {}

    [[nodiscard]] validate_return_type validate(std::string_view pw) const noexcept override {
        if (not pred_(pw)) { return error_message_; }
        else { return validate_with_next(pw); };
    }
private:
    Predicate pred_{};
    std::string error_message_{};
};


// Validating passwords
//
// Write a program that validates password strength based on predefined rules, which may be selected in various combinations.
// At a minimum, every password must meet a minimum length requirement.
// In addition, other rules could be enforced, such as the presence of at least one symbol, digit, uppercase and lowercase letter, and so on.
void problem_67_main()
{
    using namespace std::string_view_literals;

    auto contains_symbol = [](std::string_view sv) {
        return not std::all_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::isalpha(c) or std::isdigit(c); }
        );
    };
    auto contains_digit = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::isdigit(c); }
        );
    };
    auto contains_lowercase = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::islower(c); }
        );
    };
    auto contains_uppercase = [](std::string_view sv) {
        return std::any_of(std::cbegin(sv), std::cend(sv),
            [](unsigned char c) { return std::isupper(c); }
        );
    };

    for (auto&& pw : { "hola"sv, "holaquetal"sv, "holaqueta!"sv, "h0laqueta!"sv, "H0LAQUETA!"sv, "h0laQueTa!"sv })
    {
        MinimumLengthValidator validator{ 8 };
        ContainsValidator contains_symbol_validator{ contains_symbol, "password has to contain at least one 'symbol'"sv };
        ContainsValidator contains_digit_validator{ contains_digit, "password has to contain at least one 'digit'"sv };
        ContainsValidator contains_lowercase_validator{ contains_lowercase, "password has to contain at least one 'lowercase' letter"sv };
        ContainsValidator contains_uppercase_validator{ contains_uppercase, "password has to contain at least one 'uppercase' letter"sv };

        validator.set_next(&contains_symbol_validator);
        contains_symbol_validator.set_next(&contains_digit_validator);
        contains_digit_validator.set_next(&contains_lowercase_validator);
        contains_lowercase_validator.set_next(&contains_uppercase_validator);

        auto validator_result{ validator.validate(pw) };
        if (not validator_result) { std::cout << "'" << pw << "' is a valid password.\n"; }
        else { std::cout << "'" << pw << "' is not valid: " << validator_result.value() << ".\n"; }
    }

    std::cout << "\n";
}
