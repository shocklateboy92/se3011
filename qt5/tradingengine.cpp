#include "tradingengine.h"
#include "record.h"
#include <iostream>

TradingEngine::TradingEngine()
{

}


void evaluateRecord(Record r) {
    if (r.type == Record::TRADE){
        std::cout << r << endl;
    } else if (r.type == Record::ENTER && (r.askId == 0 || r.bidId == 0)) {
        r.type = Record::TRADE;
        std::cout << r << endl;
    }
}
