#ifndef _CONFIG_H
#define _CONFIG_H

#include <QDomComment>
#include <QXmlStreamWriter>

#pragma pack(1)

#define MAX_CFG_DESCRIBE (128)
typedef struct _CFG_CLIENT {
    unsigned int uiClientID;            // 客户端ID
    unsigned short usProtocol;          // 客户端协议（0：IEC104; 1：MODBUS_TCP; 2：MODBUS_SERIAL）
    char szIP[16];                      // 客户端IP（基于网络的协议）
    unsigned short usPort;              // 客户端端口（基于网络的协议）
    char szSerialDevice[16];            // 串口名称（基于串口的协议）
    int iBaud;                          // 通信波特率（基于串口的协议）
    char cParity;                       // 奇偶校验参数（基于串口的协议）
    int iDataBit;                       // 参数指定数据的位数（基于串口的协议）
    int iStopBit;                       // 参数指定停止位（基于串口的协议）
    unsigned short usSlaveID;           // 设备的从机号（IEC104协议的公共地址"PublicAddr"）
    unsigned short usGeneralCallTime;   // 总召间隔时长（单位：秒）
    char szDescribe[MAX_CFG_DESCRIBE];  // 描述
} CFG_CLIENT, *PCFG_CLIENT, **PPCFG_CLIENT;
#define MAX_CFG_CLIENT sizeof(CFG_CLIENT)

typedef struct _CFG_CLIENT_TELEMETRY {
    unsigned int uiClientTelemetryAddr;  // 客户端遥测地址
    unsigned int uiInputFlag;            // 客户端遥测?
    unsigned int uiDataType;             // 客户端遥测数据类型
    char szDescribe[MAX_CFG_DESCRIBE];   // 描述
} CFG_CLIENT_TELEMETRY, *PCFG_CLIENT_TELEMETRY, **PPCFG_CLIENT_TELEMETRY;
#define MAX_CFG_CLIENT_TELEMETRY sizeof(CFG_CLIENT_TELEMETRY)

typedef struct _CFG_CLIENT_TELESIGNA {
    unsigned int uiClientTelesignaAddr;  // 客户端遥测地址
    unsigned int uiInputFlag;            // ?
    char szDescribe[MAX_CFG_DESCRIBE];   // 描述
} CFG_CLIENT_TELESIGNA, *PCFG_CLIENT_TELESIGNA, **PPCFG_CLIENT_TELESIGNA;
#define MAX_CFG_CLIENT_TELESIGNA sizeof(CFG_CLIENT_TELESIGNA)

typedef struct _CFG_SERVER {
    unsigned int uiServerID;            // 服务端ID
    char szIP[16];                      // 服务端IP
    unsigned short usPort;              // 服务端端口
    unsigned short usDataType;          // 数据类型(5.short; 9.int; 11.float)
    unsigned short usPublicAddr;        // 公共地址
    char szDescribe[MAX_CFG_DESCRIBE];  // 描述
} CFG_SERVER, *PCFG_SERVER, **PPCFG_SERVER;
#define MAX_CFG_SERVER sizeof(CFG_SERVER)

typedef struct _CFG_SERVER_TELEMETRY {
    unsigned int uiServerTelemetryAddr;  // 服务端遥测地址
    float fCoeff;                        // 系数
    unsigned int uiClientID;             // 对应客户端ID
    unsigned int uiClientTelemetryAddr;  // 对应客户端遥测数据ID
    char szDescribe[MAX_CFG_DESCRIBE];   // 描述
} CFG_SERVER_TELEMETRY, *PCFG_SERVER_TELEMETRY, **PPCFG_SERVER_TELEMETRY;
#define MAX_CFG_SERVER_TELEMETRY sizeof(CFG_SERVER_TELEMETRY)

typedef struct _CFG_SERVER_TELESIGNA {
    unsigned int uiServerTelesignaAddr;  // 服务端遥信地址
    unsigned int uiClientID;             // 对应客户端ID
    unsigned int uiClientTelesignaAddr;  // 对应客户端遥信数据ID
    char szDescribe[MAX_CFG_DESCRIBE];   // 描述
} CFG_SERVER_TELESIGNA, *PCFG_SERVER_TELESIGNA, **PPCFG_SERVER_TELESIGNA;
#define MAX_CFG_SERVER_TELESIGNA sizeof(CFG_SERVER_TELESIGNA)

#pragma pack()

class CGatewayServer;
class CConfig {
  public:
    CConfig();
    ~CConfig();

    bool LoadServer(const char* szXmlFileName, CGatewayServer* pGatewayServer);
    bool LoadClient(const char* szXmlFileName, CGatewayServer* pGatewayServer);

  private:
  private:
    void DisposeClientList(CGatewayServer* pGatewayServer, QDomElement& domElementClientList);
    void DisposeClient(CGatewayServer* pGatewayServer, QDomElement& domElementClient);
    void DisposeClientTelemetryList(CGatewayServer* pGatewayServer, PCFG_CLIENT pCfgClient,
                                    QDomElement& domElementClientTelemetryList);
    void DisposeClientTelesignaList(CGatewayServer* pGatewayServer, PCFG_CLIENT pCfgClient,
                                    QDomElement& domElementClientTelesignaList);
    void DisposeClientTelemetry(QDomElement& domElementClientTelemetry, PCFG_CLIENT_TELEMETRY pCfgClientTelemetry);
    void DisposeClientTelesigna(PCFG_CLIENT_TELESIGNA pCfgClientTelesigna, QDomElement& domElementClientTelesigna);

    void DisposeServerList(CGatewayServer* pGatewayServer, QDomElement& domElementServerList);
    void DisposeServer(CGatewayServer* pGatewayServer, QDomElement& domElementServer);
    void DisposeServerTelemetryList(CGatewayServer* pGatewayServer, PCFG_SERVER pCfgServer,
                                    QDomElement& domElementServerTelemetryList);
    void DisposeServerTelesignaList(CGatewayServer* pGatewayServer, PCFG_SERVER pCfgServer,
                                    QDomElement& domElementServerTelesignaList);
    void DisposeServerTelemetry(PCFG_SERVER_TELEMETRY pCfgServerTelemetry, QDomElement& domElementServerTelemetry);
    void DisposeServerTelesigna(PCFG_SERVER_TELESIGNA pCfgServerTelesigna, QDomElement& domElementServerTelesigna);
};

#endif  // _CONFIG_H
