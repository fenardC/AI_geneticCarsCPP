#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneString.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <sstream>
#include <typeinfo>

GeneticGeneString::GeneticGeneString(std::string charset, int size)
    : charset(charset)
    , code()
    , size(size) {
}

GeneticGeneString::~GeneticGeneString() {
}

GeneticGene * GeneticGeneString::clone() {
    GeneticGeneString * const gene = new GeneticGeneString(charset, size);
    gene->code = code;
    return gene;
}

bool GeneticGeneString::equals(const GeneticGene & other) const {
    bool result = false;

    try {
        const GeneticGeneString & myOther = dynamic_cast<const GeneticGeneString &>(other);
#warning to be fixed
#if 1

        if (size == myOther.size) {
            return 0 == code[0]->equals(*myOther.code[0]);
        }

#endif
    }
    catch (std::bad_cast & e)   {
        Logger::debug(std::string("GeneticGeneString::equals(): ") + std::string(e.what()));
    }

    return result;
}

GeneticGeneString * GeneticGeneString::randomGene() {
    std::stringstream builder;
    const int charsetLength = charset.length();

    for (int i = 0; i < size; i++) {
        const int index = Misc::random(0, charsetLength - 1);
        builder << charset.substr(index, 1);
    }

#warning to be fixed
#if 0
    code = builder.str();
#endif

    return this;
}

void GeneticGeneString::mutate()  {
    int count = 0;
    const std::string oldCode = code[0]->toString();

#warning TOBE DONE
#if 0

    while (count < 10 && oldCode.equals(code)) {
        randomGene();
        count++;
    }

#endif
}

std::string GeneticGeneString::getCode() const  {
    return code[0]->toString();
}

int GeneticGeneString::getSize() const {
    return size;
}

std::string & GeneticGeneString::getCharset() { /*const*/
    return charset;
}

std::vector<CObject *> & GeneticGeneString::getValue() {
    return code;
}

void GeneticGeneString::destroy() {
#warning to be finished
    charset = nullptr;
    //code = nullptr;
}

std::string GeneticGeneString::toString() const {
    return code[0]->toString();
}
