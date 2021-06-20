#ifndef MAC_ENTITY_H
#define MAC_ENTITY_H

class Equipment;

class MacEntity
{
public:
    MacEntity();
    virtual ~MacEntity(void);

    void setDevice(Equipment* e);
    Equipment* getDevice();


private:

    Equipment* m_device;

};

#endif // MAC_ENTITY_H
