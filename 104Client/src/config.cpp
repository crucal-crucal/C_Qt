#include "config.h"

#include <stdio.h>

#include <QFile>
#include <QTextCodec>

#include "gatewayServer.h"

CConfig::CConfig() {}

CConfig::~CConfig() {}

bool CConfig::LoadServer(const char* szXmlFileName, CGatewayServer* pGatewayServer) {
    bool bRet = false;
    QFile fileXml;

    fileXml.setFileName(QString::fromLocal8Bit(szXmlFileName));
    if (fileXml.open(QIODevice::ReadOnly)) {
        QDomDocument domDocument;
        QString str;

        if (domDocument.setContent(&fileXml, &str)) {
            QDomElement domElementTDS = domDocument.documentElement();

            if (domElementTDS.tagName() == QString("config")) {
                QDomElement domElementChild = domElementTDS.firstChildElement();

                while (!domElementChild.isNull()) {
                    if (domElementChild.tagName() == QString("serverList")) {
                        DisposeServerList(pGatewayServer, domElementChild);
                    }

                    domElementChild = domElementChild.nextSiblingElement();
                }

                bRet = true;
            }
        }

        fileXml.close();
    } else {
        QString strError = fileXml.errorString();

        printf("%s\n", strError.toLocal8Bit().data());
    }

    return bRet;
}

bool CConfig::LoadClient(const char* szXmlFileName, CGatewayServer* pGatewayServer) {
    bool bRet = false;
    QFile fileXml;

    fileXml.setFileName(QString::fromLocal8Bit(szXmlFileName));
    if (fileXml.open(QIODevice::ReadOnly)) {
        QDomDocument domDocument;
        QString str;

        if (domDocument.setContent(&fileXml, &str)) {
            QDomElement domElementTDS = domDocument.documentElement();

            if (domElementTDS.tagName() == QString("config")) {
                QDomElement domElementChild = domElementTDS.firstChildElement();

                while (!domElementChild.isNull()) {
                    if (domElementChild.tagName() == QString("clientList")) {
                        DisposeClientList(pGatewayServer, domElementChild);
                    }

                    domElementChild = domElementChild.nextSiblingElement();
                }

                bRet = true;
            }
        }

        fileXml.close();
    } else {
        QString strError = fileXml.errorString();

        printf("%s\n", strError.toLocal8Bit().data());
    }

    return bRet;
}

void CConfig::DisposeClientList(CGatewayServer* pGatewayServer, QDomElement& domElementDeviceList) {
    QDomElement domElementChild = domElementDeviceList.firstChildElement();

    while (!domElementChild.isNull()) {
        if (domElementChild.tagName() == QString("client")) {
            DisposeClient(pGatewayServer, domElementChild);
        }

        domElementChild = domElementChild.nextSiblingElement();
    }
}

void CConfig::DisposeClient(CGatewayServer* pGatewayServer, QDomElement& domElementDevice) {
    QDomElement domElementChild = domElementDevice.firstChildElement();
    CFG_CLIENT cfgClient;

    memset(&cfgClient, 0, MAX_CFG_CLIENT);
    while (!domElementChild.isNull()) {
        if (domElementChild.tagName() == QString("id")) {
            cfgClient.uiClientID = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("protocol")) {
            cfgClient.usProtocol = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("ip")) {
            strncpy(cfgClient.szIP, domElementChild.text().toLocal8Bit().data(), 16);
        } else if (domElementChild.tagName() == QString("port")) {
            cfgClient.usPort = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("device")) {
            strcpy(cfgClient.szSerialDevice, domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("baud")) {
            cfgClient.iBaud = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("parity")) {
            cfgClient.cParity = domElementChild.text().toLocal8Bit().data()[0];
        } else if (domElementChild.tagName() == QString("dataBit")) {
            cfgClient.iDataBit = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("stopBit")) {
            cfgClient.iStopBit = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("slaveID")) {
            cfgClient.usSlaveID = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("generalCallTime")) {
            cfgClient.usGeneralCallTime = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("describe")) {
            strcpy(cfgClient.szDescribe, domElementChild.text().toLocal8Bit().data());
            pGatewayServer->AddClient(&cfgClient);
        } else if (domElementChild.tagName() == QString("telemetryList")) {
            DisposeClientTelemetryList(pGatewayServer, &cfgClient, domElementChild);
        } else if (domElementChild.tagName() == QString("telesignaList")) {
            DisposeClientTelesignaList(pGatewayServer, &cfgClient, domElementChild);
        }

        domElementChild = domElementChild.nextSiblingElement();
    }
}

void CConfig::DisposeClientTelemetryList(CGatewayServer* pGatewayServer, PCFG_CLIENT pCfgClient,
                                         QDomElement& domElementClientTelemetryList) {
    if (pCfgClient) {
        QDomElement domElementChild = domElementClientTelemetryList.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("telemetry")) {
                CFG_CLIENT_TELEMETRY cfgClientTelemetry;

                memset(&cfgClientTelemetry, 0, MAX_CFG_CLIENT_TELEMETRY);
                DisposeClientTelemetry(domElementChild, &cfgClientTelemetry);

                pGatewayServer->AddClientTelemetry(pCfgClient->uiClientID, pCfgClient->usProtocol, &cfgClientTelemetry);
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeClientTelemetry(QDomElement& domElementClientTelemetry,
                                     PCFG_CLIENT_TELEMETRY pCfgClientTelemetry) {
    if (pCfgClientTelemetry) {
        QDomElement domElementChild = domElementClientTelemetry.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("addr")) {
                pCfgClientTelemetry->uiClientTelemetryAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("inputFlag")) {
                pCfgClientTelemetry->uiInputFlag = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("dataType")) {
                pCfgClientTelemetry->uiDataType = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("dataType")) {
                pCfgClientTelemetry->uiDataType = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("describe")) {
                strcpy(pCfgClientTelemetry->szDescribe, domElementChild.text().toLocal8Bit().data());
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeClientTelesignaList(CGatewayServer* pGatewayServer, PCFG_CLIENT pCfgClient,
                                         QDomElement& domElementClientTelesignaList) {
    if (pGatewayServer && pCfgClient) {
        QDomElement domElementChild = domElementClientTelesignaList.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("telesigna")) {
                CFG_CLIENT_TELESIGNA cfgClientTelesigna;

                memset(&cfgClientTelesigna, 0, MAX_CFG_CLIENT_TELESIGNA);
                DisposeClientTelesigna(&cfgClientTelesigna, domElementChild);
                pGatewayServer->AddClientTelesigna(pCfgClient->uiClientID, pCfgClient->usProtocol, &cfgClientTelesigna);
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeClientTelesigna(PCFG_CLIENT_TELESIGNA pCfgClientTelesigna,
                                     QDomElement& domElementClientTelesigna) {
    if (pCfgClientTelesigna) {
        QDomElement domElementChild = domElementClientTelesigna.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("addr")) {
                pCfgClientTelesigna->uiClientTelesignaAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("inputFlag")) {
                pCfgClientTelesigna->uiInputFlag = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("describe")) {
                strcpy(pCfgClientTelesigna->szDescribe, domElementChild.text().toLocal8Bit().data());
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeServerList(CGatewayServer* pGatewayServer, QDomElement& domElementServerList) {
    QDomElement domElementChild = domElementServerList.firstChildElement();

    while (!domElementChild.isNull()) {
        if (domElementChild.tagName() == QString("server")) {
            DisposeServer(pGatewayServer, domElementChild);
        }

        domElementChild = domElementChild.nextSiblingElement();
    }
}

void CConfig::DisposeServer(CGatewayServer* pGatewayServer, QDomElement& domElementServer) {
    QDomElement domElementChild = domElementServer.firstChildElement();
    CFG_SERVER cfgServer;

    memset(&cfgServer, 0, MAX_CFG_SERVER);
    while (!domElementChild.isNull()) {
        if (domElementChild.tagName() == QString("id")) {
            cfgServer.uiServerID = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("ip")) {
            strncpy(cfgServer.szIP, domElementChild.text().toLocal8Bit().data(), 16);
        } else if (domElementChild.tagName() == QString("port")) {
            cfgServer.usPort = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("dataType")) {
            cfgServer.usDataType = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("publicAddr")) {
            cfgServer.usPublicAddr = atoi(domElementChild.text().toLocal8Bit().data());
        } else if (domElementChild.tagName() == QString("describe")) {
            strcpy(cfgServer.szDescribe, domElementChild.text().toLocal8Bit().data());

            pGatewayServer->AddServer(&cfgServer);
        } else if (domElementChild.tagName() == QString("telemetryList")) {
            DisposeServerTelemetryList(pGatewayServer, &cfgServer, domElementChild);
        } else if (domElementChild.tagName() == QString("telesignaList")) {
            DisposeServerTelesignaList(pGatewayServer, &cfgServer, domElementChild);
        }

        domElementChild = domElementChild.nextSiblingElement();
    }
}

void CConfig::DisposeServerTelemetryList(CGatewayServer* pGatewayServer, PCFG_SERVER pCfgServer,
                                         QDomElement& domElementServerTelemetryList) {
    if (pGatewayServer && pCfgServer) {
        QDomElement domElementChild = domElementServerTelemetryList.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("telemetry")) {
                CFG_SERVER_TELEMETRY cfgServerTelemetry;

                memset(&cfgServerTelemetry, 0, MAX_CFG_SERVER_TELEMETRY);
                DisposeServerTelemetry(&cfgServerTelemetry, domElementChild);
                pGatewayServer->AddServerTelemetry(pCfgServer->uiServerID, pCfgServer->usDataType, &cfgServerTelemetry);
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeServerTelemetry(PCFG_SERVER_TELEMETRY pCfgServerTelemetry,
                                     QDomElement& domElementServerTelemetry) {
    if (pCfgServerTelemetry) {
        QDomElement domElementChild = domElementServerTelemetry.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("addr")) {
                pCfgServerTelemetry->uiServerTelemetryAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("coeff")) {
                pCfgServerTelemetry->fCoeff = atof(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("clientID")) {
                pCfgServerTelemetry->uiClientID = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("clientTelemetryAddr")) {
                pCfgServerTelemetry->uiClientTelemetryAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("describe")) {
                strcpy(pCfgServerTelemetry->szDescribe, domElementChild.text().toLocal8Bit().data());
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeServerTelesignaList(CGatewayServer* pGatewayServer, PCFG_SERVER pCfgServer,
                                         QDomElement& domElementServerTelesignaList) {
    if (pGatewayServer && pCfgServer) {
        QDomElement domElementChild = domElementServerTelesignaList.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("telesigna")) {
                CFG_SERVER_TELESIGNA cfgServerTelesigna;

                memset(&cfgServerTelesigna, 0, MAX_CFG_SERVER_TELESIGNA);
                DisposeServerTelesigna(&cfgServerTelesigna, domElementChild);
                pGatewayServer->AddServerTelesigna(pCfgServer->uiServerID, &cfgServerTelesigna);
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}

void CConfig::DisposeServerTelesigna(PCFG_SERVER_TELESIGNA pCfgServerTelesigna,
                                     QDomElement& domElementServerTelesigna) {
    if (pCfgServerTelesigna) {
        QDomElement domElementChild = domElementServerTelesigna.firstChildElement();

        while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("addr")) {
                pCfgServerTelesigna->uiServerTelesignaAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("clientID")) {
                pCfgServerTelesigna->uiClientID = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("clientTelesignaAddr")) {
                pCfgServerTelesigna->uiClientTelesignaAddr = atoi(domElementChild.text().toLocal8Bit().data());
            } else if (domElementChild.tagName() == QString("describe")) {
                strcpy(pCfgServerTelesigna->szDescribe, domElementChild.text().toLocal8Bit().data());
            }

            domElementChild = domElementChild.nextSiblingElement();
        }
    }
}
