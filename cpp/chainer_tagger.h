
#ifndef INCLUDE_CHAINER_TAGGER_H_
#define INCLUDE_CHAINER_TAGGER_H_

#include <memory>
#include <vector>
#include <string>
#include <stdlib.h>
#include <utility>
#include "cat.h"
#include "utils.h"

namespace myccg {
namespace tagger {


class Tagger
{
public:
    virtual std::unique_ptr<float[]> predict(const std::string& tokens) const = 0;

    virtual int TargetSize() const = 0;

    virtual const cat::Category* TagAt(int idx) const  = 0;

    // virtual std::vector<std::unique_ptr<float[]>> predict(const std::vector<std::string>& doc) const = 0;
};

class ChainerTagger: public Tagger
{
public:
    ChainerTagger(const std::string& model)
    : model_(model), targets_(utils::load_category_list(model + "/target.txt")) {}
 
    std::unique_ptr<float[]> predict(const std::string& tokens) const;

    int TargetSize() const { return this->targets_.size(); }

    const cat::Category* TagAt(int idx) const { return targets_[idx]; }

    // std::vector<std::unique_ptr<float[]>> predict(const std::vector<std::string>& doc);

private:
    const std::string& model_;
    std::vector<const cat::Category*> targets_;

};

int test();
        
} // namespace tagger
} // namespace myccg

#endif