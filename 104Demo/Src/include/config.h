#ifndef _CONFIG_H
#define _CONFIG_H

#include <QDebug>
#include <QDomComment>
#include <QObject>
#include <QString>
#include <QXmlStreamWriter>
#include <iostream>
#include <map>
#include <vector>

#pragma pack(1)

// 传给服务端对应的客户端信息
enum clientType {
  telemetry = 0x01,           // 遥测对应客户端ID
  telesigna = 0x02,           // 遥信对应客户端ID
  cleint_telemetryID = 0x03,  // 对应客户端遥测数据ID
  client_telesignaID = 0x04   // 对应客户端遥信数据ID
};

typedef enum _ENUM_POINT_TYPE {
  EPT_UINT8 = 0,          // 无符号8位整型
  EPT_INT8 = 1,           // 有符号8位整型
  EPT_UINT16_NET = 2,     // 无符号16位网络字节序整型
  EPT_INT16_NET = 3,      // 有符号16位网络字节序整型
  EPT_UINT16_LOCAL = 4,   // 无符号16位主机字节序整型
  EPT_INT16_LOCAL = 5,    // 有符号16位主机字节序整型
  EPT_UINT32_NET = 6,     // 无符号32位网络字节序整型
  EPT_INT32_NET = 7,      // 有符号32位网络字节序整型
  EPT_UINT32_LOCAL = 8,   // 无符号32位主机字节序整型
  EPT_INT32_LOCAL = 9,    // 有符号32位主机字节序整型
  EPT_FLOAT_NET = 10,     // 浮点型网络字节序
  EPT_FLOAT_LOCAL = 11,   // 浮点型主机字节序
  EPT_DOUBLE_NET = 12,    // 双精度浮点型网络字节序
  EPT_DOUBLE_LOCAL = 13,  // 双精度浮点型主机字节序
} ENUM_POINT_TYPE;

#define MAX_CFG_DESCRIBE (128)

using tvalue = std::pair<QString, unsigned int>;
using tmap = std::map<tvalue, QString>;

typedef struct _CFG_CLIENT {
  unsigned int uiClientID;  // 客户端ID
  unsigned short
      usProtocol;  // 客户端协议（0：IEC104; 1：MODBUS_TCP; 2：MODBUS_SERIAL）
  char szIP[16];            // 客户端IP（基于网络的协议）
  unsigned short usPort;    // 客户端端口（基于网络的协议）
  char szSerialDevice[16];  // 串口名称（基于串口的协议）
  unsigned int iBaud;       // 通信波特率（基于串口的协议）
  unsigned int cParity;     // 奇偶校验参数（基于串口的协议）
  unsigned int iDataBit;  // 参数指定数据的位数（基于串口的协议）
  unsigned int iStopBit;  // 参数指定停止位（基于串口的协议）
  unsigned short usSlaveID;  // 设备的从机号（IEC104协议的公共地址"PublicAddr"）
  unsigned short usGeneralCallTime;   // 总召间隔时长（单位：秒）
  char szDescribe[MAX_CFG_DESCRIBE];  // 描述

  bool operator==(const _CFG_CLIENT& other) const {
    if (uiClientID != other.uiClientID) return false;
    if (usProtocol != other.usProtocol) return false;
    if (strcmp(szIP, other.szIP) != 0) return false;
    if (usPort != other.usPort) return false;
    if (strcmp(szSerialDevice, other.szSerialDevice) != 0) return false;
    if (iBaud != other.iBaud) return false;
    if (cParity != other.cParity) return false;
    if (iDataBit != other.iDataBit) return false;
    if (iStopBit != other.iStopBit) return false;
    if (usSlaveID != other.usSlaveID) return false;
    if (usGeneralCallTime != other.usGeneralCallTime) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }
  friend std::ostream& operator<<(std::ostream& os,
                                  const _CFG_CLIENT& telemetry) {
    os << telemetry.uiClientID << std::endl;
    os << telemetry.usProtocol << std::endl;
    os << telemetry.szIP << std::endl;
    os << telemetry.usPort << std::endl;
    os << telemetry.szSerialDevice << std::endl;
    os << telemetry.iBaud << std::endl;
    os << telemetry.iDataBit << std::endl;
    os << telemetry.iStopBit << std::endl;
    os << telemetry.usSlaveID << std::endl;
    os << telemetry.usGeneralCallTime << std::endl;
    os << telemetry.szDescribe << std::endl;
    return os;
  }

  bool operator!=(const _CFG_CLIENT& other) const { return !operator==(other); }
} CFG_CLIENT, *PCFG_CLIENT, **PPCFG_CLIENT;
#define MAX_CFG_CLIENT sizeof(CFG_CLIENT)
typedef std::map<unsigned int, CFG_CLIENT> MAP_CFG_CLIENT;
typedef std::vector<CFG_CLIENT> VECTOR_CFG_CLIENT, *PVECTOR_CFG_CLIENT;

typedef struct _CFG_CLIENT_TELEMETRY {
  unsigned int uiClientTelemetryAddr;  // 客户端遥测地址
  unsigned int uiInputFlag;            // 客户端遥测?
  unsigned int uiDataType;             // 客户端遥测数据类型
  char szDescribe[MAX_CFG_DESCRIBE];   // 描述

  bool operator==(const _CFG_CLIENT_TELEMETRY& other) const {
    if (uiClientTelemetryAddr != other.uiClientTelemetryAddr) return false;
    if (uiInputFlag != other.uiInputFlag) return false;
    if (uiDataType != other.uiDataType) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }

  bool operator!=(const _CFG_CLIENT_TELEMETRY& other) const {
    return !operator==(other);
  }

  bool isEmpty() const {
    return uiClientTelemetryAddr == 0 && uiInputFlag == 0 && uiDataType == 0 &&
           strlen(szDescribe) == 1 && szDescribe[0] == '0';
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const _CFG_CLIENT_TELEMETRY& telemetry) {
    os << telemetry.uiClientTelemetryAddr << std::endl;
    os << telemetry.uiInputFlag << std::endl;
    os << telemetry.uiDataType << std::endl;
    os << telemetry.szDescribe << std::endl;
    return os;
  }
} CFG_CLIENT_TELEMETRY, *PCFG_CLIENT_TELEMETRY, **PPCFG_CLIENT_TELEMETRY;
#define MAX_CFG_CLIENT_TELEMETRY sizeof(CFG_CLIENT_TELEMETRY)
typedef std::vector<CFG_CLIENT_TELEMETRY> VECTOR_CFG_CLIENT_TELEMETRY,
    *PVECTOR_CFG_CLIENT_TELEMETRY;
typedef std::map<unsigned int, VECTOR_CFG_CLIENT_TELEMETRY>
    MAP_CFG_CLIENT_TELEMETRY;

using VECTOR_CLIENT_TELEMETRY = std::vector<VECTOR_CFG_CLIENT_TELEMETRY>;

typedef struct _CFG_CLIENT_TELESIGNA {
  unsigned int uiClientTelesignaAddr;  // 客户端遥测地址
  unsigned int uiInputFlag;            // ?
  char szDescribe[MAX_CFG_DESCRIBE];   // 描述

  bool operator==(const _CFG_CLIENT_TELESIGNA& other) const {
    if (uiClientTelesignaAddr != other.uiClientTelesignaAddr) return false;
    if (uiInputFlag != other.uiInputFlag) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }

  bool operator!=(const _CFG_CLIENT_TELESIGNA& other) const {
    return !operator==(other);
  }

  bool isEmpty() const {
    return uiClientTelesignaAddr == 0 && uiInputFlag == 0 &&
           strlen(szDescribe) == 1 && szDescribe[0] == '0';
  }

} CFG_CLIENT_TELESIGNA, *PCFG_CLIENT_TELESIGNA, **PPCFG_CLIENT_TELESIGNA;
#define MAX_CFG_CLIENT_TELESIGNA sizeof(CFG_CLIENT_TELESIGNA)
typedef std::vector<CFG_CLIENT_TELESIGNA> VECTOR_CFG_CLIENT_TELESIGNA,
    *PVECTOR_CFG_CLIENT_TELESIGNA;
typedef std::map<unsigned int, VECTOR_CFG_CLIENT_TELESIGNA>
    MAP_CFG_CLIENT_TELESIGNA;

using VECTOR_CLIENT_TELESIGNA = std::vector<VECTOR_CFG_CLIENT_TELESIGNA>;

typedef struct _CFG_SERVER {
  unsigned int uiServerID;            // 服务端ID
  char szIP[16];                      // 服务端IP
  unsigned short usPort;              // 服务端端口
  unsigned short usDataType;          // 数据类型(5.short; 9.int; 11.float)
  unsigned short usPublicAddr;        // 公共地址
  char szDescribe[MAX_CFG_DESCRIBE];  // 描述

  bool operator==(const _CFG_SERVER& other) const {
    if (uiServerID != other.uiServerID) return false;
    if (strcmp(szIP, other.szIP) != 0) return false;
    if (usPort != other.usPort) return false;
    if (usDataType != other.usDataType) return false;
    if (usPublicAddr != other.usPublicAddr) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }

  bool operator!=(const _CFG_SERVER& other) const { return !operator==(other); }
} CFG_SERVER, *PCFG_SERVER, **PPCFG_SERVER;
#define MAX_CFG_SERVER sizeof(CFG_SERVER)
typedef std::map<unsigned int, CFG_SERVER> MAP_CFG_SERVER;
typedef std::vector<CFG_SERVER> VECTOR_CFG_SERVER, *PVECTOR_CFG_SERVER;

typedef struct _CFG_SERVER_TELEMETRY {
  unsigned int uiServerTelemetryAddr;  // 服务端遥测地址
  float fCoeff;                        // 系数
  unsigned int uiClientID;             // 对应客户端ID
  unsigned int uiClientTelemetryAddr;  // 对应客户端遥测数据ID
  char szDescribe[MAX_CFG_DESCRIBE];   // 描述

  bool operator==(const _CFG_SERVER_TELEMETRY& other) const {
    if (uiServerTelemetryAddr != other.uiServerTelemetryAddr) return false;
    if (fCoeff != other.fCoeff) return false;
    if (uiClientID != other.uiClientID) return false;
    if (uiClientTelemetryAddr != other.uiClientTelemetryAddr) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }

  bool operator!=(const _CFG_SERVER_TELEMETRY& other) const {
    return !operator==(other);
  }

  bool isEmpty() const {
    return uiServerTelemetryAddr == 0 && fCoeff == 0 && uiClientID == 0 &&
           uiClientTelemetryAddr == 0 && strlen(szDescribe) == 1 &&
           szDescribe[0] == '0';
  }

} CFG_SERVER_TELEMETRY, *PCFG_SERVER_TELEMETRY, **PPCFG_SERVER_TELEMETRY;
#define MAX_CFG_SERVER_TELEMETRY sizeof(CFG_SERVER_TELEMETRY)
typedef std::vector<CFG_SERVER_TELEMETRY> VECTOR_CFG_SERVER_TELEMETRY,
    *PVECTOR_CFG_SERVER_TELEMETRY;
typedef std::map<unsigned int, VECTOR_CFG_SERVER_TELEMETRY>
    MAP_CFG_SERVER_TELEMETRY;

typedef struct _CFG_SERVER_TELESIGNA {
  unsigned int uiServerTelesignaAddr;  // 服务端遥信地址
  unsigned int uiClientID;             // 对应客户端ID
  unsigned int uiClientTelesignaAddr;  // 对应客户端遥信数据ID
  char szDescribe[MAX_CFG_DESCRIBE];   // 描述

  bool operator==(const _CFG_SERVER_TELESIGNA& other) const {
    if (uiServerTelesignaAddr != other.uiServerTelesignaAddr) return false;
    if (uiClientID != other.uiClientID) return false;
    if (uiClientTelesignaAddr != other.uiClientTelesignaAddr) return false;
    if (strcmp(szDescribe, other.szDescribe) != 0) return false;

    return true;
  }

  bool operator!=(const _CFG_SERVER_TELESIGNA& other) const {
    return !operator==(other);
  }

  bool isEmpty() const {
    return uiServerTelesignaAddr == 0 && uiClientID == 0 &&
           uiClientTelesignaAddr == 0 && szDescribe[0] == '0' &&
           strlen(szDescribe) == 1;
  }
} CFG_SERVER_TELESIGNA, *PCFG_SERVER_TELESIGNA, **PPCFG_SERVER_TELESIGNA;
#define MAX_CFG_SERVER_TELESIGNA sizeof(CFG_SERVER_TELESIGNA)
typedef std::vector<CFG_SERVER_TELESIGNA> VECTOR_CFG_SERVER_TELESIGNA,
    *PVECTOR_CFG_SERVER_TELESIGNA;
typedef std::map<unsigned int, VECTOR_CFG_SERVER_TELESIGNA>
    MAP_CFG_SERVER_TELESIGNA;

#pragma pack()

class CConfig : public QObject {
  Q_OBJECT

 public:
  CConfig();
  ~CConfig();

  bool LoadFile(const char* szXmlFileName);
  bool Save();
  bool SaveAs(const char* szXmlFileName);

  bool GetClientList(PPCFG_CLIENT ppCfgClient, int* piClientSize);
  bool GetClientTelemetry(const unsigned int uiClientID,
                          PPCFG_CLIENT_TELEMETRY ppCfgClientTelemetry,
                          int* piClientTelemetrySize);
  bool GetClientTelesigna(const unsigned int uiClientID,
                          PPCFG_CLIENT_TELESIGNA ppCfgClientTelesigna,
                          int* piClientTelesignaSize);

  bool GetServerList(PPCFG_SERVER ppCfgServer, int* piServerSize);
  bool GetServerTelemetry(const unsigned int uiClientID,
                          PPCFG_SERVER_TELEMETRY ppCfgServerTelemetry,
                          int* piServerTelemetrySize);
  bool GetServerTelesigna(const unsigned int uiClientID,
                          PPCFG_SERVER_TELESIGNA ppCfgServerTelesigna,
                          int* piServerTelesignaSize);

  bool ClientAdd(const PCFG_CLIENT pCfgClient);
  bool ClientDelete(const unsigned int uiClientID);
  bool ClientModify(PCFG_CLIENT pCfgClient);

  bool ClientTelemetryAdd(const unsigned int uiClientID,
                          PCFG_CLIENT_TELEMETRY pCfgClientTelemetry);
  bool ClientTelemetryDelete(const unsigned int uiClientID,
                             const unsigned int uiClientTelemetryAddr);
  bool ClientTelemetryModify(const unsigned int uiClientID,
                             PCFG_CLIENT_TELEMETRY pCfgClientTelemetry);

  bool ClientTelesignaAdd(const unsigned int uiClientID,
                          PCFG_CLIENT_TELESIGNA pCfgClientTelesigna);
  bool ClientTelesignaDelete(const unsigned int uiClientID,
                             const unsigned int uiClientTelesignaAddr);
  bool ClientTelesignaModify(const unsigned int uiClientID,
                             PCFG_CLIENT_TELESIGNA pCfgClientTelesigna);

  bool ServerAdd(const PCFG_SERVER pCfgServer);
  bool ServerDelete(const unsigned int uiServerID);
  bool ServerModify(PCFG_SERVER pCfgServer);

  bool ServerTelemetryAdd(const unsigned int uiServerID,
                          PCFG_SERVER_TELEMETRY pCfgServerTelemetry);
  bool ServerTelemetryDelete(const unsigned int uiServerID,
                             const unsigned int uiServerTelemetryAddr);
  bool ServerTelemetryModify(const unsigned int uiServerID,
                             PCFG_SERVER_TELEMETRY pCfgServerTelemetry);

  bool ServerTelesignaAdd(const unsigned int uiServerID,
                          PCFG_SERVER_TELESIGNA pCfgServerTelesigna);
  bool ServerTelesignaDelete(const unsigned int uiServerID,
                             const unsigned int uiServerTelesignaAddr);
  bool ServerTelesignaModify(const unsigned int uiServerID,
                             PCFG_SERVER_TELESIGNA pCfgServerTelesigna);

  void ui_Save(MAP_CFG_SERVER ui_Server,
               MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
               MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
               MAP_CFG_CLIENT ui_Client,
               MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
               MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna);

  void ui_Save_As(QString filepath, MAP_CFG_SERVER ui_Server,
                  MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                  MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
                  MAP_CFG_CLIENT ui_Client,
                  MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                  MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna);

  //    void Show();

 private:
  QString m_strFileName;
  bool m_bLoad;

  MAP_CFG_CLIENT m_mapCfgClient;
  MAP_CFG_CLIENT_TELEMETRY m_mapCfgClientTelemetry;
  MAP_CFG_CLIENT_TELESIGNA m_mapCfgClientTelesigna;

  MAP_CFG_SERVER m_mapCfgServer;
  MAP_CFG_SERVER_TELEMETRY m_mapCfgServerTelemetry;
  MAP_CFG_SERVER_TELESIGNA m_mapCfgServerTelesigna;

 signals:
  void cfg_server_mes(MAP_CFG_SERVER, MAP_CFG_SERVER_TELEMETRY,
                      MAP_CFG_SERVER_TELESIGNA);
  void cfg_client_mes(MAP_CFG_CLIENT, MAP_CFG_CLIENT_TELEMETRY,
                      MAP_CFG_CLIENT_TELESIGNA);

 private:
  bool Write(QXmlStreamWriter& xmlStream);
  bool WriteServerList(QXmlStreamWriter& xmlStream);
  bool WriteServerTelemetryList(const unsigned int uiServerID,
                                QXmlStreamWriter& xmlStream);
  bool WriteServerTelesignaList(const unsigned int uiServerID,
                                QXmlStreamWriter& xmlStream);
  bool WriteClientList(QXmlStreamWriter& xmlStream);
  bool WriteClientTelemetryList(const unsigned int uiClientID,
                                QXmlStreamWriter& xmlStream);
  bool WriteClientTelesignaList(const unsigned int uiClientID,
                                QXmlStreamWriter& xmlStream);

  void DisposeClientList(QDomElement& domElementClientList);
  void DisposeClient(QDomElement& domElementClient);
  void DisposeClientTelemetryList(PCFG_CLIENT pCfgClient,
                                  QDomElement& domElementClientTelemetryList);
  void DisposeClientTelesignaList(PCFG_CLIENT pCfgClient,
                                  QDomElement& domElementClientTelesignaList);
  void DisposeClientTelemetry(QDomElement& domElementClientTelemetry,
                              PCFG_CLIENT_TELEMETRY pCfgClientTelemetry);
  void DisposeClientTelesigna(PCFG_CLIENT_TELESIGNA pCfgClientTelesigna,
                              QDomElement& domElementClientTelesigna);

  void DisposeServerList(QDomElement& domElementServerList);
  void DisposeServer(QDomElement& domElementServer);
  void DisposeServerTelemetryList(PCFG_SERVER pCfgServer,
                                  QDomElement& domElementServerTelemetryList);
  void DisposeServerTelesignaList(PCFG_SERVER pCfgServer,
                                  QDomElement& domElementServerTelesignaList);
  void DisposeServerTelemetry(PCFG_SERVER_TELEMETRY pCfgServerTelemetry,
                              QDomElement& domElementServerTelemetry);
  void DisposeServerTelesigna(PCFG_SERVER_TELESIGNA pCfgServerTelesigna,
                              QDomElement& domElementServerTelesigna);
};

#endif  // _CONFIG_H
