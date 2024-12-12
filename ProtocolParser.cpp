class ProtocolParser {
public:
    ProtocolParser() : currentState(Idle) {}

    void parseData(const QByteArray &data) {
        for (char byte : data) {
            switch (currentState) {
            case Idle:
                if (byte == 0x01) currentState = Header;
                break;
            case Header:
                // 解析头部数据
                currentState = Body;
                break;
            case Body:
                // 解析消息体
                currentState = Complete;
                break;
            case Complete:
                // 处理完成
                currentState = Idle;
                break;
            }
        }
    }

private:
    enum State { Idle, Header, Body, Complete };
    State currentState;
};
