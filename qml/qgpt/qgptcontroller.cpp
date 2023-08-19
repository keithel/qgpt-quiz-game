#include "qgptcontroller.h"

#include <QtConcurrent>
#include <QVariant>
#include <QJsonParseError>
#include <QJsonDocument>

#include <liboai/include/core/authorization.h>
#include <liboai/include/core/response.h>
#include <string>
#include <exception>
#include <iostream>

using liboai::Authorization;
using liboai::Response;

QGptController::QGptController(QObject *parent)
    : QObject(parent)
{
    Authorization::Authorizer().SetMaxTimeout(60000);
    auto isApiKeyOk = openAi.auth.SetKeyEnv("OPENAI_API_KEY");

    if (isApiKeyOk) {
        QtConcurrent::run([this]{
            try {
                setProperty("state", QVariant::fromValue(State::GENERATING));
                Response response = openAi.Completion->create(
                    "text-davinci-003"
                    "Generate a set of 5 multiple choice questions (in quiz style) about Software "
                    "Architecture. For each question, generate five possible answers and indicate "
                    "the right one. Your response should be just a JSON array with objects using "
                    "the following keys: 'question_description', 'answers' (array of possible "
                    "answers), and 'right_answer' (index of right answer in possible answers "
                    "array).",
                    std::nullopt,
                    3000);
                auto string = QString::fromStdString(response["choices"][0]["text"].get<std::string>())
                    .remove(u"\n"_qs)
                    .remove(u"\t"_qs)
                    .replace('\'', '"');
                QJsonParseError error;
                auto document = QJsonDocument:fromJson(string.toLatin1, &error);
                setProperty("questions", document.array());
                setProperty("state", QVariant::fromValue(State::READY));
            }
            catch (std::exception &e) {
                std::cout << "Exception: " << e.what() << std::endl;
            }
        });
    }
}
