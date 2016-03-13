#include <iostream>
#include <cstdlib>
#include <vector>
#include "gamestate.h"
#include "client.h"

using namespace std;

/** General messages **/

void handleConnectMsg(vector<string> args) {
}

void handleLeftMsg(vector<string> args) {
}


/** Idle Phase Messages **/

void handleWelcomeMsg(vector<string> args) {
}

void handleSessionMsg(vector<string> args) {
}

void handleTurnMsg(vector<string> args) {
}

/** Thinking Phase Messages **/

void handleUFoundMsg(vector<string> args) {
}

void handleHeFoundMsg(vector<string> args) {
}

void handleEndThinkMsg(vector<string> args) {
}


/** Auction Phase Messages **/

void handleYouBidMsg(vector<string> args) {
}

void handleHeBidsMsg(vector<string> args) {
}

void handleEndAuctionMsg(vector<string> args) {
}


/** Solving Phase Messages **/

void handleHisSolMsg(vector<string> args) {
}

void HandleGoodSolMsg(vector<string> args) {
}

void handleBadSolMsg(vector<string> args) {
}

void handleEndSolveMsg(vector<string> args) {
}

void handleTimeoutMsg(vector<string> args) {
}

void handleWinnerMsg(vector<string> args) {
}
