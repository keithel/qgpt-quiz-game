class QGptController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QGptController::State state MEMBER mState NOTIFY stateChanged)
    Q_PROPERTY(QJsonArray questions MEMBER mQuestions NOTIFY questionsChanged)

public:
    enum class State { GENERATING = 0; READY };
    Q_ENUM(State)

    explicit QGptController(QObject *parent = nullptr);

signals:
    void stateChanged(QGptController::State state);
    void questionsChanged(const QJsonArray &questions);

private:
    liboai::OpenAI openAi;
    State mState;
    QJsonArray mQuestions;
};
