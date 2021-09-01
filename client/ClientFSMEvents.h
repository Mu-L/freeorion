#ifndef _ClientFSMEvents_h_
#define _ClientFSMEvents_h_

#include "../network/Message.h"

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/statechart/event.hpp>


// Non-Message events
struct Disconnection : boost::statechart::event<Disconnection> {};


//  Message events
/** The base class for all state machine events that are based on Messages. */
struct MessageEventBase {
    explicit MessageEventBase(Message&& message) :
        m_message{std::move(message)}
    {}
    Message m_message;
};

// Define Boost.Preprocessor list of all Message events
#define MESSAGE_EVENTS                         \
    (DispatchCombatLogs)                       \
    (Error)                                    \
    (HostMPGame)                               \
    (HostSPGame)                               \
    (JoinGame)                                 \
    (HostID)                                   \
    (LobbyUpdate)                              \
    (LobbyChat)                                \
    (SaveGameComplete)                         \
    (GameStart)                                \
    (TurnUpdate)                               \
    (TurnPartialUpdate)                        \
    (TurnProgress)                             \
    (TurnRevoked)                              \
    (PlayerStatus)                             \
    (PlayerChat)                               \
    (Diplomacy)                                \
    (DiplomaticStatusUpdate)                   \
    (EndGame)                                  \
    (CheckSum)                                 \
    (AuthRequest)                              \
    (ChatHistory)                              \
    (TurnTimeout)                              \
    (PlayerInfoMsg)


#define DECLARE_MESSAGE_EVENT(r, data, name)                            \
    struct name :                                                       \
        boost::statechart::event<name>,                                 \
        MessageEventBase                                                \
    {                                                                   \
        name(Message&& message) :                                       \
            MessageEventBase(std::move(message)) {}                     \
    };

BOOST_PP_SEQ_FOR_EACH(DECLARE_MESSAGE_EVENT, _, MESSAGE_EVENTS)

#undef DECLARE_MESSAGE_EVENT

#endif
