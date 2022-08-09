//
// Created by b0n3 on 8/3/22.
//

#ifndef VEEZEN2RTMP_UUID_H
#define VEEZEN2RTMP_UUID_H
#include <random>
#include <sstream>
#include <FBString.h>
#include <boost/regex.hpp>
#include <ostream>

namespace uuid {
    class UUID {
    private:
        folly::fbstring _id;
        std::random_device rd;

        std::mt19937 gen;

        std::uniform_int_distribution<> dis;

        std::uniform_int_distribution<> dis2;

        void genrateStringId();

        static bool validate(folly::fbstring &id);

    public:
        UUID();
        uuid::UUID &getRef();
         UUID(const UUID &uuid);
        friend std::ostream &operator<<(std::ostream &os, const UUID &uuid1);

        UUID(std::unique_ptr<UUID>  uuid);

        static std::shared_ptr<UUID> fromString(folly::fbstring uuid);

        static std::unique_ptr<UUID> generateRandomUUID();

        bool operator==(const UUID &rhs) const;

        bool operator!=(const UUID &rhs) const;

        bool operator<(const UUID &rhs) const;

        bool operator>(const UUID &rhs) const;

        bool operator<=(const UUID &rhs) const;

        bool operator>=(const UUID &rhs) const;

        folly::fbstring getId();

                class UUIDException : public std::exception {
        public:
            std::string message;

            UUIDException(const std::string &message) : message(message) {}

            const char *what() const noexcept override {
                return message.c_str();
            }
        };
    };
}
#endif //VEEZEN2RTMP_UUID_H
