#include "Src/include/config.h"

#include <stdio.h>

#include <QFile>
#include <QTextCodec>

CConfig::CConfig() { m_bLoad = false; }

CConfig::~CConfig() {}

bool CConfig::LoadFile(const char* szXmlFileName) {
  this->m_mapCfgServer.clear();
  this->m_mapCfgServerTelemetry.clear();
  this->m_mapCfgServerTelesigna.clear();

  this->m_mapCfgClient.clear();
  this->m_mapCfgClientTelemetry.clear();
  this->m_mapCfgClientTelesigna.clear();
  if (szXmlFileName) {
    bool bRet = false;
    QFile fileXml;

    fileXml.setFileName(QString::fromUtf8(szXmlFileName));
    if (fileXml.open(QIODevice::ReadOnly)) {
      qDebug() << "open successful!";
      QDomDocument domDocument;
      QString str;

      m_strFileName = szXmlFileName;
      if (domDocument.setContent(&fileXml, &str)) {
        qDebug() << "setContent successful!";
        QDomElement domElementTDS = domDocument.documentElement();

        if (domElementTDS.tagName() == QString("config")) {
          QDomElement domElementChild = domElementTDS.firstChildElement();

          while (!domElementChild.isNull()) {
            if (domElementChild.tagName() == QString("serverList")) {
              DisposeServerList(domElementChild);
            } else if (domElementChild.tagName() == QString("clientList")) {
              DisposeClientList(domElementChild);
            }

            domElementChild = domElementChild.nextSiblingElement();
          }

          m_bLoad = true;
          bRet = true;
        }
      }

      emit cfg_client_mes(m_mapCfgClient, m_mapCfgClientTelemetry,
                          m_mapCfgClientTelesigna);
      emit cfg_server_mes(m_mapCfgServer, m_mapCfgServerTelemetry,
                          m_mapCfgServerTelesigna);

      fileXml.close();
    } else {
      QString strError = fileXml.errorString();

      printf("%s\n", strError.toUtf8().constData());
    }

    return bRet;
  }

  return false;
}

bool CConfig::Save() {
  if (m_bLoad) {
    return SaveAs(m_strFileName.toStdString().c_str());
  }

  return false;
}

bool CConfig::SaveAs(const char* szXmlFileName) {
  qDebug() << szXmlFileName;
  if (szXmlFileName) {
    if (m_bLoad) {
      QFile fileXml;

      fileXml.setFileName(QString::fromUtf8(szXmlFileName));
      if (fileXml.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter xmlStream(&fileXml);

        xmlStream.setAutoFormatting(true);
        xmlStream.setCodec(QTextCodec::codecForName("utf-8"));
        xmlStream.writeStartDocument();

        Write(xmlStream);
        fileXml.close();
      }

      return true;
    }
  }

  return false;
}

bool CConfig::WriteServerTelemetryList(const unsigned int uiServerID,
                                       QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("telemetryList");
  {
    MAP_CFG_SERVER_TELEMETRY::iterator it =
        m_mapCfgServerTelemetry.find(uiServerID);
    if (it != m_mapCfgServerTelemetry.end()) {
      PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

      pVectorCfgServerTelemetry = &it->second;
      if (!pVectorCfgServerTelemetry->empty()) {
        for (size_t i = 0; i < pVectorCfgServerTelemetry->size(); i++) {
          PCFG_SERVER_TELEMETRY pCfgServerTelemetry = NULL;

          pCfgServerTelemetry = &pVectorCfgServerTelemetry->data()[i];
          xmlStream.writeStartElement("telemetry");
          {
            xmlStream.writeTextElement(
                "addr",
                QString::number(pCfgServerTelemetry->uiServerTelemetryAddr));
            xmlStream.writeTextElement(
                "coeff", QString::number(pCfgServerTelemetry->fCoeff));
            xmlStream.writeTextElement(
                "clientID", QString::number(pCfgServerTelemetry->uiClientID));
            xmlStream.writeTextElement(
                "clientTelemetryAddr",
                QString::number(pCfgServerTelemetry->uiClientTelemetryAddr));
            xmlStream.writeTextElement(
                "describe", QString::fromUtf8(pCfgServerTelemetry->szDescribe));
          }
          xmlStream.writeEndElement();
        }
      } else {
        qDebug() << "pVectorCfgServerTelemetry is Empty";
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::WriteServerTelesignaList(const unsigned int uiServerID,
                                       QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("telesignaList");
  {
    MAP_CFG_SERVER_TELESIGNA::iterator it =
        m_mapCfgServerTelesigna.find(uiServerID);

    if (it != m_mapCfgServerTelesigna.end()) {
      PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

      pVectorCfgServerTelesigna = &it->second;
      if (!pVectorCfgServerTelesigna->empty()) {
        for (size_t i = 0; i < pVectorCfgServerTelesigna->size(); i++) {
          PCFG_SERVER_TELESIGNA pCfgServerTelesigna = NULL;

          pCfgServerTelesigna = &pVectorCfgServerTelesigna->data()[i];
          xmlStream.writeStartElement("telesigna");
          {
            xmlStream.writeTextElement(
                "addr",
                QString::number(pCfgServerTelesigna->uiServerTelesignaAddr));
            xmlStream.writeTextElement(
                "clientID", QString::number(pCfgServerTelesigna->uiClientID));
            xmlStream.writeTextElement(
                "telesignaID",
                QString::number(pCfgServerTelesigna->uiClientTelesignaAddr));
            xmlStream.writeTextElement(
                "describe", QString::fromUtf8(pCfgServerTelesigna->szDescribe));
          }
          xmlStream.writeEndElement();
        }
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::WriteServerList(QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("serverList");
  {
    if (m_mapCfgServer.size()) {
      for (MAP_CFG_SERVER::iterator it = m_mapCfgServer.begin();
           it != m_mapCfgServer.end(); it++) {
        PCFG_SERVER pCfgServer = NULL;

        pCfgServer = &it->second;
        if (pCfgServer) {
          xmlStream.writeStartElement("server");
          {
            xmlStream.writeTextElement("id",
                                       QString::number(pCfgServer->uiServerID));
            xmlStream.writeTextElement("ip", pCfgServer->szIP);
            xmlStream.writeTextElement("port",
                                       QString::number(pCfgServer->usPort));
            xmlStream.writeTextElement("dataType",
                                       QString::number(pCfgServer->usDataType));
            xmlStream.writeTextElement(
                "publicAddr", QString::number(pCfgServer->usPublicAddr));
            xmlStream.writeTextElement(
                "describe", QString::fromUtf8(pCfgServer->szDescribe));

            WriteServerTelemetryList(pCfgServer->uiServerID, xmlStream);
            WriteServerTelesignaList(pCfgServer->uiServerID, xmlStream);
          }
          xmlStream.writeEndElement();
        }
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::WriteClientList(QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("clientList");
  {
    if (m_mapCfgClient.size()) {
      for (MAP_CFG_CLIENT::iterator it = m_mapCfgClient.begin();
           it != m_mapCfgClient.end(); it++) {
        PCFG_CLIENT pCfgClient = NULL;

        pCfgClient = &it->second;
        if (pCfgClient) {
          xmlStream.writeStartElement("client");
          {
            xmlStream.writeTextElement("id",
                                       QString::number(pCfgClient->uiClientID));
            xmlStream.writeTextElement("protocol",
                                       QString::number(pCfgClient->usProtocol));
            xmlStream.writeTextElement("ip", pCfgClient->szIP);
            xmlStream.writeTextElement("port",
                                       QString::number(pCfgClient->usPort));

            xmlStream.writeTextElement("serialDevice",
                                       pCfgClient->szSerialDevice);
            xmlStream.writeTextElement("baud",
                                       QString::number(pCfgClient->iBaud));
            xmlStream.writeTextElement("parity",
                                       QString::number(pCfgClient->cParity));
            xmlStream.writeTextElement("dataBit",
                                       QString::number(pCfgClient->iDataBit));
            xmlStream.writeTextElement("stopBit",
                                       QString::number(pCfgClient->iStopBit));

            xmlStream.writeTextElement("slaveID",
                                       QString::number(pCfgClient->usSlaveID));
            xmlStream.writeTextElement(
                "generalCallTime",
                QString::number(pCfgClient->usGeneralCallTime));
            xmlStream.writeTextElement(
                "describe", QString::fromUtf8(pCfgClient->szDescribe));

            WriteClientTelemetryList(pCfgClient->uiClientID, xmlStream);
            WriteClientTelesignaList(pCfgClient->uiClientID, xmlStream);
          }
          xmlStream.writeEndElement();
        }
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::WriteClientTelemetryList(const unsigned int uiServerID,
                                       QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("telemetryList");
  {
    MAP_CFG_CLIENT_TELEMETRY::iterator it =
        m_mapCfgClientTelemetry.find(uiServerID);

    if (it != m_mapCfgClientTelemetry.end()) {
      PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

      pVectorCfgClientTelemetry = &it->second;
      for (size_t i = 0; i < pVectorCfgClientTelemetry->size(); i++) {
        PCFG_CLIENT_TELEMETRY pCfgClientTelemetry = NULL;

        pCfgClientTelemetry = &pVectorCfgClientTelemetry->data()[i];
        xmlStream.writeStartElement("telemetry");
        {
          xmlStream.writeTextElement(
              "addr",
              QString::number(pCfgClientTelemetry->uiClientTelemetryAddr));
          xmlStream.writeTextElement(
              "inputFlag", QString::number(pCfgClientTelemetry->uiInputFlag));
          xmlStream.writeTextElement(
              "dataType", QString::number(pCfgClientTelemetry->uiDataType));
          xmlStream.writeTextElement(
              "describe", QString::fromUtf8(pCfgClientTelemetry->szDescribe));
        }
        xmlStream.writeEndElement();
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::WriteClientTelesignaList(const unsigned int uiClientID,
                                       QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("telesignaList");
  {
    MAP_CFG_CLIENT_TELESIGNA::iterator it =
        m_mapCfgClientTelesigna.find(uiClientID);

    if (it != m_mapCfgClientTelesigna.end()) {
      PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

      pVectorCfgClientTelesigna = &it->second;
      for (size_t i = 0; i < pVectorCfgClientTelesigna->size(); i++) {
        PCFG_CLIENT_TELESIGNA pCfgClientTelesigna = NULL;

        pCfgClientTelesigna = &pVectorCfgClientTelesigna->data()[i];
        xmlStream.writeStartElement("telesigna");
        {
          xmlStream.writeTextElement(
              "addr",
              QString::number(pCfgClientTelesigna->uiClientTelesignaAddr));
          xmlStream.writeTextElement(
              "inputFlag", QString::number(pCfgClientTelesigna->uiInputFlag));
          xmlStream.writeTextElement(
              "describe", QString::fromUtf8(pCfgClientTelesigna->szDescribe));
        }
        xmlStream.writeEndElement();
      }
    }
  }
  xmlStream.writeEndElement();
  return true;
}

bool CConfig::Write(QXmlStreamWriter& xmlStream) {
  xmlStream.writeStartElement("config");

  {
    WriteServerList(xmlStream);
    WriteClientList(xmlStream);
  }

  xmlStream.writeEndElement();
  xmlStream.writeEndDocument();

  return true;
}

bool CConfig::GetClientList(PPCFG_CLIENT ppCfgClient, int* piClientSize) {
  if (ppCfgClient && piClientSize) {
    static VECTOR_CFG_CLIENT vectorCfgClient;

    vectorCfgClient.clear();
    if (m_mapCfgClient.size()) {
      for (MAP_CFG_CLIENT::iterator it = m_mapCfgClient.begin();
           it != m_mapCfgClient.end(); it++) {
        PCFG_CLIENT pCfgClient = NULL;

        pCfgClient = &it->second;

        vectorCfgClient.push_back(*pCfgClient);
      }

      *ppCfgClient = vectorCfgClient.data();
      *piClientSize = vectorCfgClient.size();

      return true;
    }
  }

  return false;
}

bool CConfig::GetClientTelemetry(const unsigned int uiClientID,
                                 PPCFG_CLIENT_TELEMETRY ppCfgClientTelemetry,
                                 int* piClientTelemetrySize) {
  if (ppCfgClientTelemetry && piClientTelemetrySize) {
    MAP_CFG_CLIENT_TELEMETRY::iterator it =
        m_mapCfgClientTelemetry.find(uiClientID);

    if (it != m_mapCfgClientTelemetry.end()) {
      PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

      pVectorCfgClientTelemetry = &it->second;
      *ppCfgClientTelemetry = pVectorCfgClientTelemetry->data();
      *piClientTelemetrySize = pVectorCfgClientTelemetry->size();

      return true;
    }
  }

  return false;
}

bool CConfig::GetClientTelesigna(const unsigned int uiClientID,
                                 PPCFG_CLIENT_TELESIGNA ppCfgClientTelesigna,
                                 int* piClientTelesignaSize) {
  if (ppCfgClientTelesigna && piClientTelesignaSize) {
    MAP_CFG_CLIENT_TELESIGNA::iterator it =
        m_mapCfgClientTelesigna.find(uiClientID);

    if (it != m_mapCfgClientTelesigna.end()) {
      PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

      pVectorCfgClientTelesigna = &it->second;
      *ppCfgClientTelesigna = pVectorCfgClientTelesigna->data();
      *piClientTelesignaSize = pVectorCfgClientTelesigna->size();

      return true;
    }
  }

  return false;
}

bool CConfig::GetServerList(PPCFG_SERVER ppCfgServer, int* piServerSize) {
  if (ppCfgServer && piServerSize) {
    static VECTOR_CFG_SERVER vectorCfgServer;

    vectorCfgServer.clear();
    if (m_mapCfgServer.size()) {
      for (MAP_CFG_SERVER::iterator it = m_mapCfgServer.begin();
           it != m_mapCfgServer.end(); it++) {
        PCFG_SERVER pCfgServer = NULL;

        pCfgServer = &it->second;

        vectorCfgServer.push_back(*pCfgServer);
      }

      *ppCfgServer = vectorCfgServer.data();
      *piServerSize = vectorCfgServer.size();

      return true;
    }
  }

  return false;
}

bool CConfig::GetServerTelemetry(const unsigned int uiClientID,
                                 PPCFG_SERVER_TELEMETRY ppCfgServerTelemetry,
                                 int* piServerTelemetrySize) {
  if (ppCfgServerTelemetry && piServerTelemetrySize) {
    MAP_CFG_SERVER_TELEMETRY::iterator it =
        m_mapCfgServerTelemetry.find(uiClientID);

    if (it != m_mapCfgServerTelemetry.end()) {
      PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

      pVectorCfgServerTelemetry = &it->second;
      *ppCfgServerTelemetry = pVectorCfgServerTelemetry->data();
      *piServerTelemetrySize = pVectorCfgServerTelemetry->size();

      return true;
    }
  }

  return false;
}

bool CConfig::GetServerTelesigna(const unsigned int uiClientID,
                                 PPCFG_SERVER_TELESIGNA ppCfgServerTelesigna,
                                 int* piServerTelesignaSize) {
  if (ppCfgServerTelesigna && piServerTelesignaSize) {
    MAP_CFG_SERVER_TELESIGNA::iterator it =
        m_mapCfgServerTelesigna.find(uiClientID);

    if (it != m_mapCfgServerTelesigna.end()) {
      PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

      pVectorCfgServerTelesigna = &it->second;
      *ppCfgServerTelesigna = pVectorCfgServerTelesigna->data();
      *piServerTelesignaSize = pVectorCfgServerTelesigna->size();

      return true;
    }
  }

  return false;
}

/*
void CConfig::Show() {
    printf("------------ Client[%d] ------------\n", m_mapCfgClient.size());
    for (MAP_CFG_CLIENT::iterator it = m_mapCfgClient.begin(); it !=
m_mapCfgClient.end(); it++) { PCFG_CLIENT pCfgClient = NULL;

        pCfgClient = &it->second;

        printf("\t[id = %d][projct = %d][%s:%d]\n", pCfgClient->uiClientID,
pCfgClient->usProtocol, pCfgClient->szIP, pCfgClient->usPort);
        MAP_CFG_CLIENT_TELEMETRY::iterator itTelemetry =
m_mapCfgClientTelemetry.find(pCfgClient->uiClientID); if (itTelemetry !=
m_mapCfgClientTelemetry.end()) { PVECTOR_CFG_CLIENT_TELEMETRY
pVectorCfgClientTelemetry = NULL;

            pVectorCfgClientTelemetry = &itTelemetry->second;
            printf("\t------------- telemetry -------------\n");
            for (int i = 0; i < pVectorCfgClientTelemetry->size(); i++) {
                printf("\t[%d][%d][%d][%s]\n",
pVectorCfgClientTelemetry->data()[i].uiClientTelemetryAddr,
                       pVectorCfgClientTelemetry->data()[i].uiInputFlag,
                       pVectorCfgClientTelemetry->data()[i].uiDataType,
                       pVectorCfgClientTelemetry->data()[i].szDescribe);
            }
        }

        MAP_CFG_CLIENT_TELESIGNA::iterator itTeleigna =
m_mapCfgClientTelesigna.find(pCfgClient->uiClientID); if (itTeleigna !=
m_mapCfgClientTelesigna.end()) { PVECTOR_CFG_CLIENT_TELESIGNA
pVectorCfgClientTelesigna = NULL;

            pVectorCfgClientTelesigna = &itTeleigna->second;
            printf("\t------------- telesigna -------------\n");
            for (int i = 0; i < pVectorCfgClientTelesigna->size(); i++) {
                printf("\t[%d][%d][%s]\n",
pVectorCfgClientTelesigna->data()[i].uiClientTelesignaAddr,
                       pVectorCfgClientTelesigna->data()[i].uiInputFlag,
                       pVectorCfgClientTelesigna->data()[i].szDescribe);
            }
        }
    }

    printf("------------ Server[%d] ------------\n", m_mapCfgServer.size());
    for (MAP_CFG_SERVER::iterator it = m_mapCfgServer.begin(); it !=
m_mapCfgServer.end(); it++) { PCFG_SERVER pCfgServer = NULL;

        pCfgServer = &it->second;

        printf("\t[id = %d][%s:%d][dataType = %d][publicAddr = %d]\n",
pCfgServer->uiServerID, pCfgServer->szIP, pCfgServer->usPort,
pCfgServer->usDataType, pCfgServer->usPublicAddr);
        MAP_CFG_SERVER_TELEMETRY::iterator itTelemetry =
m_mapCfgServerTelemetry.find(pCfgServer->uiServerID); if (itTelemetry !=
m_mapCfgServerTelemetry.end()) { PVECTOR_CFG_SERVER_TELEMETRY
pVectorCfgServerTelemetry = NULL;

            pVectorCfgServerTelemetry = &itTelemetry->second;
            printf("\t------------- telemetry -------------\n");
            for (int i = 0; i < pVectorCfgServerTelemetry->size(); i++) {
                printf("\t[%d][%f][%d][%d][%s]\n",
pVectorCfgServerTelemetry->data()[i].uiServerTelemetryAddr,
                       pVectorCfgServerTelemetry->data()[i].fCoeff,
pVectorCfgServerTelemetry->data()[i].uiClientID,
                       pVectorCfgServerTelemetry->data()[i].uiClientTelemetryAddr,
                       pVectorCfgServerTelemetry->data()[i].szDescribe);
            }
        }

        MAP_CFG_SERVER_TELESIGNA::iterator itTeleigna =
m_mapCfgServerTelesigna.find(pCfgServer->uiServerID); if (itTeleigna !=
m_mapCfgServerTelesigna.end()) { PVECTOR_CFG_SERVER_TELESIGNA
pVectorCfgServerTelesigna = NULL;

            pVectorCfgServerTelesigna = &itTeleigna->second;
            printf("\t------------- telesigna -------------\n");
            for (int i = 0; i < pVectorCfgServerTelesigna->size(); i++) {
                printf("\t[%d][%d][%d][%s]\n",
pVectorCfgServerTelesigna->data()[i].uiServerTelesignaAddr,
                       pVectorCfgServerTelesigna->data()[i].uiClientID,
                       pVectorCfgServerTelesigna->data()[i].uiClientTelesignaAddr,
                       pVectorCfgServerTelesigna->data()[i].szDescribe);
            }
        }
    }

    return;
}
*/

void CConfig::DisposeClientList(QDomElement& domElementDeviceList) {
  QDomElement domElementChild = domElementDeviceList.firstChildElement();

  while (!domElementChild.isNull()) {
    if (domElementChild.tagName() == QString("client")) {
      DisposeClient(domElementChild);
    }

    domElementChild = domElementChild.nextSiblingElement();
  }
}

void CConfig::DisposeClient(QDomElement& domElementDevice) {
  QDomElement domElementChild = domElementDevice.firstChildElement();
  CFG_CLIENT cfgClient;

  memset(&cfgClient, 0, MAX_CFG_CLIENT);
  while (!domElementChild.isNull()) {
    if (domElementChild.tagName() == QString("id")) {
      cfgClient.uiClientID = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("protocol")) {
      cfgClient.usProtocol = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("ip")) {
      qstrncpy(cfgClient.szIP, domElementChild.text().toUtf8().constData(), 16);
    } else if (domElementChild.tagName() == QString("port")) {
      cfgClient.usPort = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("serialDevice")) {
      qstrncpy(cfgClient.szSerialDevice,
               domElementChild.text().toUtf8().constData(), MAX_CFG_DESCRIBE);
    } else if (domElementChild.tagName() == QString("baud")) {
      cfgClient.iBaud = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("parity")) {
      cfgClient.cParity = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("dataBit")) {
      cfgClient.iDataBit = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("stopBit")) {
      cfgClient.iStopBit = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("slaveID")) {
      cfgClient.usSlaveID = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("generalCallTime")) {
      cfgClient.usGeneralCallTime =
          atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("describe")) {
      VECTOR_CFG_CLIENT_TELEMETRY vectorCfgClientTelemetry;
      VECTOR_CFG_CLIENT_TELESIGNA vectorCfgClientTelesigna;

      qstrncpy(cfgClient.szDescribe,
               domElementChild.text().toUtf8().constData(), MAX_CFG_DESCRIBE);

      m_mapCfgClient.insert(
          MAP_CFG_CLIENT::value_type(cfgClient.uiClientID, cfgClient));
      m_mapCfgClientTelemetry.insert(MAP_CFG_CLIENT_TELEMETRY::value_type(
          cfgClient.uiClientID, vectorCfgClientTelemetry));
      m_mapCfgClientTelesigna.insert(MAP_CFG_CLIENT_TELESIGNA::value_type(
          cfgClient.uiClientID, vectorCfgClientTelesigna));
    } else if (domElementChild.tagName() == QString("telemetryList")) {
      DisposeClientTelemetryList(&cfgClient, domElementChild);
    } else if (domElementChild.tagName() == QString("telesignaList")) {
      DisposeClientTelesignaList(&cfgClient, domElementChild);
    }

    domElementChild = domElementChild.nextSiblingElement();
  }
}

void CConfig::DisposeClientTelemetryList(
    PCFG_CLIENT pCfgClient, QDomElement& domElementClientTelemetryList) {
  if (pCfgClient) {
    QDomElement domElementChild =
        domElementClientTelemetryList.firstChildElement();

    while (!domElementChild.isNull()) {
      if (domElementChild.tagName() == QString("telemetry")) {
        CFG_CLIENT_TELEMETRY cfgClientTelemetry;

        memset(&cfgClientTelemetry, 0, MAX_CFG_CLIENT_TELEMETRY);
        DisposeClientTelemetry(domElementChild, &cfgClientTelemetry);

        MAP_CFG_CLIENT_TELEMETRY::iterator it =
            m_mapCfgClientTelemetry.find(pCfgClient->uiClientID);
        if (it != m_mapCfgClientTelemetry.end()) {
          PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

          pVectorCfgClientTelemetry = &it->second;
          pVectorCfgClientTelemetry->push_back(cfgClientTelemetry);
        }
      }

      domElementChild = domElementChild.nextSiblingElement();
    }
  }
}

void CConfig::DisposeClientTelemetry(
    QDomElement& domElementClientTelemetry,
    PCFG_CLIENT_TELEMETRY pCfgClientTelemetry) {
  if (pCfgClientTelemetry) {
    QDomElement domElementChild = domElementClientTelemetry.firstChildElement();

    while (!domElementChild.isNull()) {
      if (domElementChild.tagName() == QString("addr")) {
        pCfgClientTelemetry->uiClientTelemetryAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("inputFlag")) {
        pCfgClientTelemetry->uiInputFlag =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("dataType")) {
        pCfgClientTelemetry->uiDataType =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("dataType")) {
        pCfgClientTelemetry->uiDataType =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("describe")) {
        qstrcpy(pCfgClientTelemetry->szDescribe,
                domElementChild.text().toUtf8().constData());
      }

      domElementChild = domElementChild.nextSiblingElement();
    }
  }
}

void CConfig::DisposeClientTelesignaList(
    PCFG_CLIENT pCfgClient, QDomElement& domElementClientTelesignaList) {
  if (pCfgClient) {
    QDomElement domElementChild =
        domElementClientTelesignaList.firstChildElement();

    while (!domElementChild.isNull()) {
      if (domElementChild.tagName() == QString("telesigna")) {
        CFG_CLIENT_TELESIGNA cfgClientTelesigna;

        memset(&cfgClientTelesigna, 0, MAX_CFG_CLIENT_TELESIGNA);
        DisposeClientTelesigna(&cfgClientTelesigna, domElementChild);

        MAP_CFG_CLIENT_TELESIGNA::iterator it =
            m_mapCfgClientTelesigna.find(pCfgClient->uiClientID);
        if (it != m_mapCfgClientTelesigna.end()) {
          PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

          pVectorCfgClientTelesigna = &it->second;
          pVectorCfgClientTelesigna->push_back(cfgClientTelesigna);
        }
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
        pCfgClientTelesigna->uiClientTelesignaAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("inputFlag")) {
        pCfgClientTelesigna->uiInputFlag =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("describe")) {
        qstrcpy(pCfgClientTelesigna->szDescribe,
                domElementChild.text().toUtf8().constData());
      }

      domElementChild = domElementChild.nextSiblingElement();
    }
  }
}

void CConfig::DisposeServerList(QDomElement& domElementServerList) {
  QDomElement domElementChild = domElementServerList.firstChildElement();
  while (!domElementChild.isNull()) {
    if (domElementChild.tagName() == QString("server")) {
      DisposeServer(domElementChild);
    }

    domElementChild = domElementChild.nextSiblingElement();
  }
}

void CConfig::DisposeServer(QDomElement& domElementServer) {
  QDomElement domElementChild = domElementServer.firstChildElement();
  CFG_SERVER cfgServer;

  memset(&cfgServer, 0, MAX_CFG_SERVER);
  while (!domElementChild.isNull()) {
    if (domElementChild.tagName() == QString("id")) {
      cfgServer.uiServerID = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("ip")) {
      qstrncpy(cfgServer.szIP, domElementChild.text().toUtf8().constData(), 16);
    } else if (domElementChild.tagName() == QString("port")) {
      cfgServer.usPort = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("dataType")) {
      cfgServer.usDataType = atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("publicAddr")) {
      cfgServer.usPublicAddr =
          atoi(domElementChild.text().toUtf8().constData());
    } else if (domElementChild.tagName() == QString("describe")) {
      VECTOR_CFG_SERVER_TELEMETRY vectorCfgServerTelemetry;
      VECTOR_CFG_SERVER_TELESIGNA vectorCfgServerTelesigna;

      qstrcpy(cfgServer.szDescribe,
              domElementChild.text().toUtf8().constData());

      m_mapCfgServer.insert(
          MAP_CFG_SERVER::value_type(cfgServer.uiServerID, cfgServer));
      m_mapCfgServerTelemetry.insert(MAP_CFG_SERVER_TELEMETRY::value_type(
          cfgServer.uiServerID, vectorCfgServerTelemetry));
      m_mapCfgServerTelesigna.insert(MAP_CFG_SERVER_TELESIGNA::value_type(
          cfgServer.uiServerID, vectorCfgServerTelesigna));
    } else if (domElementChild.tagName() == QString("telemetryList")) {
      DisposeServerTelemetryList(&cfgServer, domElementChild);
    } else if (domElementChild.tagName() == QString("telesignaList")) {
      DisposeServerTelesignaList(&cfgServer, domElementChild);
    }

    domElementChild = domElementChild.nextSiblingElement();
  }
}

void CConfig::DisposeServerTelemetryList(
    PCFG_SERVER pCfgServer, QDomElement& domElementServerTelemetryList) {
  if (pCfgServer) {
    QDomElement domElementChild =
        domElementServerTelemetryList.firstChildElement();

    while (!domElementChild.isNull()) {
      if (domElementChild.tagName() == QString("telemetry")) {
        CFG_SERVER_TELEMETRY cfgServerTelemetry;

        memset(&cfgServerTelemetry, 0, MAX_CFG_SERVER_TELEMETRY);
        DisposeServerTelemetry(&cfgServerTelemetry, domElementChild);

        MAP_CFG_SERVER_TELEMETRY::iterator it =
            m_mapCfgServerTelemetry.find(pCfgServer->uiServerID);
        if (it != m_mapCfgServerTelemetry.end()) {
          PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

          pVectorCfgServerTelemetry = &it->second;
          pVectorCfgServerTelemetry->push_back(cfgServerTelemetry);
        }
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
        pCfgServerTelemetry->uiServerTelemetryAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("coeff")) {
        pCfgServerTelemetry->fCoeff =
            atof(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("clientID")) {
        pCfgServerTelemetry->uiClientID =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("clientTelemetryAddr")) {
        pCfgServerTelemetry->uiClientTelemetryAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("describe")) {
        qstrcpy(pCfgServerTelemetry->szDescribe,
                domElementChild.text().toUtf8().constData());
      }

      domElementChild = domElementChild.nextSiblingElement();
    }
  }
}

void CConfig::DisposeServerTelesignaList(
    PCFG_SERVER pCfgServer, QDomElement& domElementServerTelesignaList) {
  if (pCfgServer) {
    QDomElement domElementChild =
        domElementServerTelesignaList.firstChildElement();

    while (!domElementChild.isNull()) {
      if (domElementChild.tagName() == QString("telesigna")) {
        CFG_SERVER_TELESIGNA cfgServerTelesigna;

        memset(&cfgServerTelesigna, 0, MAX_CFG_SERVER_TELESIGNA);
        DisposeServerTelesigna(&cfgServerTelesigna, domElementChild);

        MAP_CFG_SERVER_TELESIGNA::iterator it =
            m_mapCfgServerTelesigna.find(pCfgServer->uiServerID);
        if (it != m_mapCfgServerTelesigna.end()) {
          PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

          pVectorCfgServerTelesigna = &it->second;
          pVectorCfgServerTelesigna->push_back(cfgServerTelesigna);
        }
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
        pCfgServerTelesigna->uiServerTelesignaAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("clientID")) {
        pCfgServerTelesigna->uiClientID =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("clientTelesignaAddr")) {
        pCfgServerTelesigna->uiClientTelesignaAddr =
            atoi(domElementChild.text().toUtf8().constData());
      } else if (domElementChild.tagName() == QString("describe")) {
        strcpy(pCfgServerTelesigna->szDescribe,
               domElementChild.text().toUtf8().constData());
      }

      domElementChild = domElementChild.nextSiblingElement();
    }
  }
}

bool CConfig::ClientAdd(const PCFG_CLIENT pCfgClient) {
  if (pCfgClient) {
    MAP_CFG_CLIENT::iterator it = m_mapCfgClient.find(pCfgClient->uiClientID);

    if (it == m_mapCfgClient.end()) {
      VECTOR_CFG_CLIENT_TELEMETRY vectorCfgClientTelemetry;
      VECTOR_CFG_CLIENT_TELESIGNA vectorCfgClientTelesigna;

      m_mapCfgClient.insert(
          MAP_CFG_CLIENT::value_type(pCfgClient->uiClientID, *pCfgClient));
      m_mapCfgClientTelemetry.insert(MAP_CFG_CLIENT_TELEMETRY::value_type(
          pCfgClient->uiClientID, vectorCfgClientTelemetry));
      m_mapCfgClientTelesigna.insert(MAP_CFG_CLIENT_TELESIGNA::value_type(
          pCfgClient->uiClientID, vectorCfgClientTelesigna));

      return true;
    }
  }

  return false;
}

bool CConfig::ClientDelete(const unsigned int uiClientID) {
  MAP_CFG_CLIENT::iterator it = m_mapCfgClient.find(uiClientID);

  if (it != m_mapCfgClient.end()) {
    m_mapCfgClientTelemetry.erase(uiClientID);
    m_mapCfgClientTelesigna.erase(uiClientID);
    m_mapCfgClient.erase(uiClientID);

    return true;
  }

  return false;
}

bool CConfig::ClientModify(PCFG_CLIENT pCfgClient) {
  if (pCfgClient) {
    MAP_CFG_CLIENT::iterator it = m_mapCfgClient.find(pCfgClient->uiClientID);

    if (it != m_mapCfgClient.end()) {
      *(PCFG_CLIENT)&it->second = *pCfgClient;

      return true;
    }
  }

  return false;
}

bool CConfig::ClientTelemetryAdd(const unsigned int uiClientID,
                                 PCFG_CLIENT_TELEMETRY pCfgClientTelemetry) {
  if (pCfgClientTelemetry) {
    MAP_CFG_CLIENT_TELEMETRY::iterator it =
        m_mapCfgClientTelemetry.find(uiClientID);

    if (it != m_mapCfgClientTelemetry.end()) {
      PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

      pVectorCfgClientTelemetry = &it->second;
      // 循环遍列客户端遥测信号表，如果有相同遥测地址的信号则返回失败
      for (size_t i = 0; i < pVectorCfgClientTelemetry->size(); i++) {
        PCFG_CLIENT_TELEMETRY pCfgClientTelemetryTemp = NULL;

        pCfgClientTelemetryTemp = &pVectorCfgClientTelemetry->data()[i];
        if (pCfgClientTelemetryTemp->uiClientTelemetryAddr ==
            pCfgClientTelemetry->uiClientTelemetryAddr) {
          return false;
        }
      }

      // 将新建遥测信号追加至队列尾
      pVectorCfgClientTelemetry->push_back(*pCfgClientTelemetry);

      return true;
    }
  }

  return false;
}

bool CConfig::ClientTelemetryDelete(const unsigned int uiClientID,
                                    const unsigned int uiClientTelemetryAddr) {
  MAP_CFG_CLIENT_TELEMETRY::iterator it =
      m_mapCfgClientTelemetry.find(uiClientID);

  if (it != m_mapCfgClientTelemetry.end()) {
    PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

    pVectorCfgClientTelemetry = &it->second;
    // 循环遍列客户端遥测信号表，删除相同遥测地址的信号
    for (VECTOR_CFG_CLIENT_TELEMETRY::iterator iter =
             pVectorCfgClientTelemetry->begin();
         iter != pVectorCfgClientTelemetry->end(); iter++) {
      if (iter->uiClientTelemetryAddr == uiClientTelemetryAddr) {
        pVectorCfgClientTelemetry->erase(iter);

        return true;
      }
    }
  }

  return false;
}

bool CConfig::ClientTelemetryModify(const unsigned int uiClientID,
                                    PCFG_CLIENT_TELEMETRY pCfgClientTelemetry) {
  if (pCfgClientTelemetry) {
    MAP_CFG_CLIENT_TELEMETRY::iterator it =
        m_mapCfgClientTelemetry.find(uiClientID);

    if (it != m_mapCfgClientTelemetry.end()) {
      PVECTOR_CFG_CLIENT_TELEMETRY pVectorCfgClientTelemetry = NULL;

      pVectorCfgClientTelemetry = &it->second;
      // 循环遍列客户端遥测信号表，删除相同遥测地址的信号
      for (VECTOR_CFG_CLIENT_TELEMETRY::iterator iter =
               pVectorCfgClientTelemetry->begin();
           iter != pVectorCfgClientTelemetry->end(); iter++) {
        if (iter->uiClientTelemetryAddr ==
            pCfgClientTelemetry->uiClientTelemetryAddr) {
          *iter = *pCfgClientTelemetry;

          return true;
        }
      }
    }
  }

  return false;
}

bool CConfig::ClientTelesignaAdd(const unsigned int uiClientID,
                                 PCFG_CLIENT_TELESIGNA pCfgClientTelesigna) {
  if (pCfgClientTelesigna) {
    MAP_CFG_CLIENT_TELESIGNA::iterator it =
        m_mapCfgClientTelesigna.find(uiClientID);

    if (it != m_mapCfgClientTelesigna.end()) {
      PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

      pVectorCfgClientTelesigna = &it->second;
      // 循环遍列客户端遥测信号表，如果有相同遥测地址的信号则返回失败
      for (size_t i = 0; i < pVectorCfgClientTelesigna->size(); i++) {
        PCFG_CLIENT_TELESIGNA pCfgClientTelesignaTemp = NULL;

        pCfgClientTelesignaTemp = &pVectorCfgClientTelesigna->data()[i];
        if (pCfgClientTelesignaTemp->uiClientTelesignaAddr ==
            pCfgClientTelesigna->uiClientTelesignaAddr) {
          return false;
        }
      }

      // 将新建遥测信号追加至队列尾
      pVectorCfgClientTelesigna->push_back(*pCfgClientTelesigna);

      return true;
    }
  }

  return false;
}

bool CConfig::ClientTelesignaDelete(const unsigned int uiClientID,
                                    const unsigned int uiClientTelesignaAddr) {
  MAP_CFG_CLIENT_TELESIGNA::iterator it =
      m_mapCfgClientTelesigna.find(uiClientID);

  if (it != m_mapCfgClientTelesigna.end()) {
    PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

    pVectorCfgClientTelesigna = &it->second;
    // 循环遍列客户端遥信信号表，删除相同遥信地址的信号
    for (VECTOR_CFG_CLIENT_TELESIGNA::iterator iter =
             pVectorCfgClientTelesigna->begin();
         iter != pVectorCfgClientTelesigna->end(); iter++) {
      if (iter->uiClientTelesignaAddr == uiClientTelesignaAddr) {
        pVectorCfgClientTelesigna->erase(iter);

        return true;
      }
    }
  }

  return false;
}

bool CConfig::ClientTelesignaModify(const unsigned int uiClientID,
                                    PCFG_CLIENT_TELESIGNA pCfgClientTelesigna) {
  if (pCfgClientTelesigna) {
    MAP_CFG_CLIENT_TELESIGNA::iterator it =
        m_mapCfgClientTelesigna.find(uiClientID);

    if (it != m_mapCfgClientTelesigna.end()) {
      PVECTOR_CFG_CLIENT_TELESIGNA pVectorCfgClientTelesigna = NULL;

      pVectorCfgClientTelesigna = &it->second;
      // 循环遍列客户端遥测信号表，删除相同遥测地址的信号
      for (VECTOR_CFG_CLIENT_TELESIGNA::iterator iter =
               pVectorCfgClientTelesigna->begin();
           iter != pVectorCfgClientTelesigna->end(); iter++) {
        if (iter->uiClientTelesignaAddr ==
            pCfgClientTelesigna->uiClientTelesignaAddr) {
          *iter = *pCfgClientTelesigna;

          return true;
        }
      }
    }
  }

  return false;
}

bool CConfig::ServerAdd(const PCFG_SERVER pCfgServer) {
  if (pCfgServer) {
    MAP_CFG_SERVER::iterator it = m_mapCfgServer.find(pCfgServer->uiServerID);

    if (it == m_mapCfgServer.end()) {
      VECTOR_CFG_SERVER_TELEMETRY vectorCfgServerTelemetry;
      VECTOR_CFG_SERVER_TELESIGNA vectorCfgServerTelesigna;

      m_mapCfgServer.insert(
          MAP_CFG_SERVER::value_type(pCfgServer->uiServerID, *pCfgServer));
      m_mapCfgServerTelemetry.insert(MAP_CFG_SERVER_TELEMETRY::value_type(
          pCfgServer->uiServerID, vectorCfgServerTelemetry));
      m_mapCfgServerTelesigna.insert(MAP_CFG_SERVER_TELESIGNA::value_type(
          pCfgServer->uiServerID, vectorCfgServerTelesigna));

      return true;
    }
  }

  return false;
}

bool CConfig::ServerDelete(const unsigned int uiServerID) {
  MAP_CFG_SERVER::iterator it = m_mapCfgServer.find(uiServerID);

  if (it != m_mapCfgServer.end()) {
    m_mapCfgServerTelemetry.erase(uiServerID);
    m_mapCfgServerTelesigna.erase(uiServerID);
    m_mapCfgServer.erase(uiServerID);

    return true;
  }

  return false;
}

bool CConfig::ServerModify(PCFG_SERVER pCfgServer) {
  if (pCfgServer) {
    MAP_CFG_SERVER::iterator it = m_mapCfgServer.find(pCfgServer->uiServerID);

    if (it != m_mapCfgServer.end()) {
      *(PCFG_SERVER)&it->second = *pCfgServer;

      return true;
    }
  }

  return false;
}

bool CConfig::ServerTelemetryAdd(const unsigned int uiServerID,
                                 PCFG_SERVER_TELEMETRY pCfgServerTelemetry) {
  if (pCfgServerTelemetry) {
    MAP_CFG_SERVER_TELEMETRY::iterator it =
        m_mapCfgServerTelemetry.find(uiServerID);

    if (it != m_mapCfgServerTelemetry.end()) {
      PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

      pVectorCfgServerTelemetry = &it->second;
      // 循环遍列客户端遥测信号表，如果有相同遥测地址的信号则返回失败
      for (size_t i = 0; i < pVectorCfgServerTelemetry->size(); i++) {
        PCFG_SERVER_TELEMETRY pCfgServerTelemetryTemp = NULL;

        pCfgServerTelemetryTemp = &pVectorCfgServerTelemetry->data()[i];
        if (pCfgServerTelemetryTemp->uiServerTelemetryAddr ==
            pCfgServerTelemetry->uiServerTelemetryAddr) {
          return false;
        }
      }

      // 将新建遥测信号追加至队列尾
      pVectorCfgServerTelemetry->push_back(*pCfgServerTelemetry);

      return true;
    }
  }

  return false;
}

bool CConfig::ServerTelemetryDelete(const unsigned int uiServerID,
                                    const unsigned int uiServerTelemetryAddr) {
  MAP_CFG_SERVER_TELEMETRY::iterator it =
      m_mapCfgServerTelemetry.find(uiServerID);

  if (it != m_mapCfgServerTelemetry.end()) {
    PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

    pVectorCfgServerTelemetry = &it->second;
    // 循环遍列服务端遥测信号表，删除相同遥测地址的信号
    for (VECTOR_CFG_SERVER_TELEMETRY::iterator iter =
             pVectorCfgServerTelemetry->begin();
         iter != pVectorCfgServerTelemetry->end(); iter++) {
      if (iter->uiServerTelemetryAddr == uiServerTelemetryAddr) {
        pVectorCfgServerTelemetry->erase(iter);

        return true;
      }
    }
  }

  return false;
}

bool CConfig::ServerTelemetryModify(const unsigned int uiServerID,
                                    PCFG_SERVER_TELEMETRY pCfgServerTelemetry) {
  if (pCfgServerTelemetry) {
    MAP_CFG_SERVER_TELEMETRY::iterator it =
        m_mapCfgServerTelemetry.find(uiServerID);

    if (it != m_mapCfgServerTelemetry.end()) {
      PVECTOR_CFG_SERVER_TELEMETRY pVectorCfgServerTelemetry = NULL;

      pVectorCfgServerTelemetry = &it->second;
      // 循环遍列客户端遥测信号表，删除相同遥测地址的信号
      for (VECTOR_CFG_SERVER_TELEMETRY::iterator iter =
               pVectorCfgServerTelemetry->begin();
           iter != pVectorCfgServerTelemetry->end(); iter++) {
        if (iter->uiServerTelemetryAddr ==
            pCfgServerTelemetry->uiServerTelemetryAddr) {
          *iter = *pCfgServerTelemetry;

          return true;
        }
      }
    }
  }

  return false;
}

bool CConfig::ServerTelesignaAdd(const unsigned int uiServerID,
                                 PCFG_SERVER_TELESIGNA pCfgServerTelesigna) {
  if (pCfgServerTelesigna) {
    MAP_CFG_SERVER_TELESIGNA::iterator it =
        m_mapCfgServerTelesigna.find(uiServerID);

    if (it != m_mapCfgServerTelesigna.end()) {
      PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

      pVectorCfgServerTelesigna = &it->second;
      // 循环遍列客户端遥测信号表，如果有相同遥测地址的信号则返回失败
      for (size_t i = 0; i < pVectorCfgServerTelesigna->size(); i++) {
        PCFG_SERVER_TELESIGNA pCfgServerTelesignaTemp = NULL;

        pCfgServerTelesignaTemp = &pVectorCfgServerTelesigna->data()[i];
        if (pCfgServerTelesignaTemp->uiServerTelesignaAddr ==
            pCfgServerTelesigna->uiServerTelesignaAddr) {
          return false;
        }
      }

      // 将新建遥测信号追加至队列尾
      pVectorCfgServerTelesigna->push_back(*pCfgServerTelesigna);

      return true;
    }
  }

  return false;
}

bool CConfig::ServerTelesignaDelete(const unsigned int uiServerID,
                                    const unsigned int uiServerTelesignaAddr) {
  MAP_CFG_SERVER_TELESIGNA::iterator it =
      m_mapCfgServerTelesigna.find(uiServerID);

  if (it != m_mapCfgServerTelesigna.end()) {
    PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

    pVectorCfgServerTelesigna = &it->second;
    // 循环遍列客户端遥信信号表，删除相同遥信地址的信号
    for (VECTOR_CFG_SERVER_TELESIGNA::iterator iter =
             pVectorCfgServerTelesigna->begin();
         iter != pVectorCfgServerTelesigna->end(); iter++) {
      if (iter->uiServerTelesignaAddr == uiServerTelesignaAddr) {
        pVectorCfgServerTelesigna->erase(iter);

        return true;
      }
    }
  }

  return false;
}

bool CConfig::ServerTelesignaModify(const unsigned int uiServerID,
                                    PCFG_SERVER_TELESIGNA pCfgServerTelesigna) {
  if (pCfgServerTelesigna) {
    MAP_CFG_SERVER_TELESIGNA::iterator it =
        m_mapCfgServerTelesigna.find(uiServerID);

    if (it != m_mapCfgServerTelesigna.end()) {
      PVECTOR_CFG_SERVER_TELESIGNA pVectorCfgServerTelesigna = NULL;

      pVectorCfgServerTelesigna = &it->second;
      // 循环遍列客户端遥测信号表，删除相同遥测地址的信号
      for (VECTOR_CFG_SERVER_TELESIGNA::iterator iter =
               pVectorCfgServerTelesigna->begin();
           iter != pVectorCfgServerTelesigna->end(); iter++) {
        if (iter->uiServerTelesignaAddr ==
            pCfgServerTelesigna->uiServerTelesignaAddr) {
          *iter = *pCfgServerTelesigna;

          return true;
        }
      }
    }
  }

  return false;
}

void CConfig::ui_Save(MAP_CFG_SERVER ui_Server,
                      MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                      MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
                      MAP_CFG_CLIENT ui_Client,
                      MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                      MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna) {
  m_mapCfgServer.clear(), m_mapCfgServerTelemetry.clear(),
      m_mapCfgServerTelesigna.clear();
  m_mapCfgServer = ui_Server;
  m_mapCfgServerTelemetry = ui_ServerTelemetry;
  m_mapCfgServerTelesigna = ui_ServerTelesigna;

  m_mapCfgClient.clear(), m_mapCfgClientTelemetry.clear(),
      m_mapCfgClientTelesigna.clear();
  m_mapCfgClient = ui_Client;
  m_mapCfgClientTelemetry = ui_ClientTelemetry;
  m_mapCfgClientTelesigna = ui_ClientTelesigna;

  this->Save();
}

void CConfig::ui_Save_As(QString filepath, MAP_CFG_SERVER ui_Server,
                         MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                         MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
                         MAP_CFG_CLIENT ui_Client,
                         MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                         MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna) {
  m_mapCfgServer.clear(), m_mapCfgServerTelemetry.clear(),
      m_mapCfgServerTelesigna.clear();
  m_mapCfgServer = ui_Server;
  m_mapCfgServerTelemetry = ui_ServerTelemetry;
  m_mapCfgServerTelesigna = ui_ServerTelesigna;

  m_mapCfgClient.clear(), m_mapCfgClientTelemetry.clear(),
      m_mapCfgClientTelesigna.clear();
  m_mapCfgClient = ui_Client;
  m_mapCfgClientTelemetry = ui_ClientTelemetry;
  m_mapCfgClientTelesigna = ui_ClientTelesigna;

  this->SaveAs(filepath.toUtf8().constData());
}
