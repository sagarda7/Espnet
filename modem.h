#ifndef __MODEM_H__
#define __MODEM_H__

#include "arduino.h"
#include <SoftwareSerial.h>

#define DEFAULT_TIMEOUT     5

enum DataType {
    CMD     = 0,
    DATA    = 1,
};

/** Modem class.
 *  Used for Modem communication. attention that Modem module communicate with MCU in serial protocol
 */
class Modem
{

public:
    /** Create Modem Instance
     *  @param tx   uart transmit pin to communicate with Modem
     *  @param rx   uart receive pin to communicate with Modem
     *  @param baudRate baud rate of uart communication
     */
    Modem(int tx, int rx, int baudRate) : serialModem(tx, rx) {
        serialModem.begin(baudRate);
    };
    
protected:
    /** Power on Modem
     */
    void preInit(void);

    /** check serialModem is readable or not
     *  @returns
     *      true on readable
     *      false on not readable
     */
    bool readable();

    /** read one byte from serialModem
     *  @returns
     *      one byte read from serialModem
     */
    char readByte(void);

    /** read from Modem module and save to buffer array
     *  @param  buffer  buffer array to save what read from Modem module
     *  @param  count   the maximal bytes number read from Modem module
     *  @param  timeOut time to wait for reading from Modem module
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int readBuffer(char* buffer,int count, unsigned int timeOut);


    /** clean Buffer
     *  @param buffer   buffer to clean
     *  @param count    number of bytes to clean
     */
    void cleanBuffer(char* buffer, int count);

    /** send AT command to Modem module
     *  @param cmd  command array which will be send to GPRS module
     */
    void sendCmd(const char* cmd);

    /**send "AT" to Modem module
     */
    void sendATTest(void);

    /** compare the response from GPRS module with a string
     *  @param resp buffer to be compared
     *  @param len length that will be compared
     *  @param timeout  waiting seconds till timeout
     */
    bool respCmp(const char *resp, unsigned int len, unsigned int timeout);

    /** check Modem module response before time out
     *  @param  *resp   correct response which Modem module will return
     *  @param  *timeout    waiting seconds till timeout
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int waitForResp(const char *resp, unsigned int timeout,DataType type);

    /** send AT command to GPRS module and wait for correct response
     *  @param  *cmd    AT command which will be send to GPRS module
     *  @param  *resp   correct response which GPRS module will return
     *  @param  *timeout    waiting seconds till timeout
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int sendCmdAndWaitForResp(const char* data, const char *resp, unsigned timeout,DataType type);

    SoftwareSerial serialModem;
private:

};

#endif
