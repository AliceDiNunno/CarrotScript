//
// Created by Alice Di Nunno on 20/10/2018.
//

#ifndef CARROTCLOUDAPI_SEQUENCE_HPP
#define CARROTCLOUDAPI_SEQUENCE_HPP

#include <QVariant>
#include <QUuid>
#include <QDebug>

class SequenceTrigger;
class SequenceNode;
class Sequence {
public:
    SequenceNode *start = nullptr;
    QString triggerId;

    bool isValid();
    bool run();
};


#endif //CARROTCLOUDAPI_SEQUENCE_HPP
