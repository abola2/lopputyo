#ifndef LOPPUTYO_COLORS_H
#define LOPPUTYO_COLORS_H
//Ansi codes
namespace Color {
    const auto Reset   = "\033[0m";
    const auto Black   = "\033[30m";
    const auto Red     = "\033[31m";
    const auto Green   = "\033[32m";
    const auto Yellow  = "\033[33m";
    const auto Blue    = "\033[34m";
    const auto Magenta = "\033[35m";
    const auto Cyan    = "\033[36m";
    const auto White   = "\033[37m";

    const auto BrightBlack   = "\033[90m";
    const auto BrightRed     = "\033[91m";
    const auto BrightGreen   = "\033[92m";
    const auto BrightYellow  = "\033[93m";
    const auto BrightBlue    = "\033[94m";
    const auto BrightMagenta = "\033[95m";
    const auto BrightCyan    = "\033[96m";
    const auto BrightWhite   = "\033[97m";

    const auto Underline   = "\033[4m";
}

//Static questions
namespace Questions
{
    const std::string NAME_PROMPT = std::format(
        "{}{}{}{}\n{}> {}",
        Color::Cyan, "Mikä on nimesi?", Color::Reset, "",
        Color::Yellow, Color::Reset
        );

    const std::string BED_AMOUNT_PROMPT = std::format(
        "{}? Monenko sängyn huoneen haluat:{}\n"
        "  {}1{} ) Yhden sängyn\n"
        "  {}2{} ) Kahden sängyn\n"
        "{}> {}",
        Color::Cyan, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Yellow, Color::Reset
    );

    const std::string START_PROMPT = std::format(
        "{}? Mitä haluat tehdä:{}\n"
        "  {}1{} ) Tarkastele varauksia\n"
        "  {}2{} ) Varaa uusi huone\n"
        "  {}3{} ) Sulje ohjelma\n"
        "{}> {}",
        Color::Cyan, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Yellow, Color::Reset
    );

    const std::string BOOKING_NUMBER_PROMPT = std::format(
        "{}{}{}{}\n{}> {}",
        Color::Cyan, "Mikä on varausnumero?", Color::Reset, "",
        Color::Yellow, Color::Reset
    );

    const std::string DAY_AMOUNT_PROMPT = std::format(
       "{}{}{}{}\n{}> {}",
       Color::Cyan, "Montako yötä olet?", Color::Reset, "",
       Color::Yellow, Color::Reset
   );

    const std::string SEARCH_TYPE_PROMPT = std::format(
        "{}? Haluatko hakea:{}\n"
        "  {}1{} ) Varausnumerolla\n"
        "  {}2{} ) Nimellä\n"
        "{}> {}",
        Color::Cyan, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Yellow, Color::Reset
    );

    const std::string CONTINUE_OR_RETURN_PROMPT = std::format(
        "{}? Mitä haluat tehdä:{}\n"
        "  {}1{} ) Tehdä uuden varauksen\n"
        "  {}2{} ) Palata alkuun\n"
        "{}> {}",
        Color::Cyan, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Green, Color::Reset,
        Color::Yellow, Color::Reset
    );
}

#endif //LOPPUTYO_COLORS_H