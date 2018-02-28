#ifndef QWAVEFPGA_H
#define QWAVEFPGA_H

class QwaveFpga {
public:
	QwaveFpga();
	~QwaveFpga();
	bool begin();
    bool viExecution();
    bool viStop();
    void BusReset();
    bool writeRegister(int16_t addr, int32_t data);
    bool getRegister(int16_t addr);
    bool FpgaLoad(String bitfile);
    void Transfer_Init();
    void Transfer(int count, uint8_t * buf);
    void Transfer_End();
    void SaveFile_Init();
    void SaveFile_Encypt(uint8_t * buf, int len);
    
    union rxData{
        int32_t bit32[2];
        int8_t bit8[8];
    };
    
    rxData data;
    
private:
    
    union Address{
        int16_t bit16;
        int8_t bit8[2];
    };
    
    union Data{
        int32_t bit32;
        int8_t bit8[4];
    };
    
    uint8_t count;
};

#endif
