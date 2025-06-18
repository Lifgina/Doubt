#pragma once

#include <optional>
#include "../../HuEngine.h"
#include "CardDistributer.h"
#include "DiscardManager.h"
#include "CardDiscarder.h"
#include "RandomCardSelect.h"
#include "PlayerData.h"

class GameManager {
public:
    void Load();
    void Initialize();
    void Update();
    void DiscardTurn();
    void DoubtTurn();
    bool DoubtCheck(int doubtPlayerID, int discardPlayerID);
    void Penalty(int penaltyPlayer);
    void SetPlayerDiscard(int cardIndex[4]);
    void SetPlayerDoDoubt(bool isDoubt);
    int SetMyPlayerID(int playerID) {
        myPlayerID_ = playerID;
        return myPlayerID_;
    }
    int SetPlayerCount(int playerCount) {
        playerCount_ = playerCount;
        return playerCount_;
    }
    bool GetIsDiscardTurn() const { return isDiscardTurn_; }
    bool GetIsInputed() const { return isInputed_; }
    int GetTurnPlayerID() const { return turnPlayerID_; }
    int GetDoubtJudgeNo() const { return doubtJudgeNo_; }
    int GetDoubtPlayerID() const { return doubtplayerID_; }
    int GetWinnerPlayerID() const { return winnerPlayerID_; }
    int GetDiscardCount() const { return discardManager_.GetDiscardCount(); }
    PlayerData GetPlayerData(int playerID) const { return player_[playerID]; }

    // �_�E�g���茋�ʊǗ�
    void SetDoubtResult(bool result) { doubtResult_ = result; }
    bool IsDoubtResultAvailable() const { return doubtResult_.has_value(); }
    bool GetDoubtResult() const { return doubtResult_.value_or(false); }
    void ResetDoubtResult() { doubtResult_.reset(); }

    // ���߂̃_�E�g/�X���[�錾�Ǘ�
    std::optional<std::pair<int, bool>> GetLastDoubtAction() const { return lastDoubtAction_; }
    void ResetLastDoubtAction() { lastDoubtAction_.reset(); }

    int GetLastDoubtPlayerID() const { return lastDoubtPlayerID_; }
    void ResetLastDoubtPlayerID() { lastDoubtPlayerID_ = -1; }

private:
    int playerCount_;
    PlayerData player_[4];
    int playerDiscardIndex_[4];
    int myPlayerID_;
    int turnPlayerID_;
    int discardPlayerID_;
    int doubtJudgeNo_;
    int doubtplayerID_;
    int winnerPlayerID_;
    int lastDoubtPlayerID_ = -1; // ���߂̃_�E�g�錾��ID�iPenaltyLog�p�j
    bool isDiscardTurn_;
    bool isInputed_;
    bool isDoubt_;
    std::optional<bool> doubtResult_;

    // �ǉ�: ���߂̃_�E�g/�X���[�錾
    std::optional<std::pair<int, bool>> lastDoubtAction_;

    CardDistributer cardDistributer_;
    CardDiscarder cardDiscarder_;
    DiscardManager discardManager_;
    RandomCardSelect randomCardSelect_;
};
