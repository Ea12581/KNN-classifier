//
// Created by oem on 1/18/23.
//
#include <utility>

#include "Command.h"
#include "KnnDB.h"
#ifndef EX4_COMMANDUPLOAD_H
#define EX4_COMMANDUPLOAD_H
/**
 * class for upload CVS train and test files of KNN vectors
 */
class UploadC : public Command{
private:
    vector<KnnVec> *getMTrain() const;

    void setMTrain(vector<KnnVec> *mTrain);

    vector<VectorCalDis> *getMTest() const;

    void setMTest(vector<VectorCalDis> *mTest);
public:
    /**
     * constructor with description and dio
     * @param _desc description of the command
     * @param _dio io of the command
     */
    UploadC(string _desc, DefaultIO* _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){};
    bool uploadTrain();
    bool uploadTest();
    void execute() override;

};

#endif //EX4_COMMANDUPLOAD_H