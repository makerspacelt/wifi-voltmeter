#include "display.h"


U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void initDisplay()
{
    u8g2.begin();

    u8g2.setDrawColor(1);
    u8g2.setFontMode(0);

    u8g2.drawBox(0,0,128,32);
    u8g2.sendBuffer();

    delay(100);
    u8g2.setContrast(0);
}

void screenRepaint()
{
    u8g2.clearBuffer();

    showVoltage(false);
    showWifi(false);
    showScale(false);
    showBar(false);

    u8g2.sendBuffer();
}

void showBar(bool send)
{
    String bar = "";
    for (int i=0; i<21; i++) {
        if (state.adc_now > i*50) {
            bar += '.';
        } else {
            bar += ' ';
        }
    }
    bar += '_';

    u8g2.setFont(u8g2_font_cu12_tr);		  
    u8g2.setCursor(0,32);
    u8g2.print(bar);

    if (send) {
        u8g2.sendBuffer();
    }
}

void showWifi(bool send)
{
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.setCursor(112,16);
    switch (state.wifi) {
        case 1:
            u8g2.write(207); // connecting
            break;
        case 2:
            u8g2.write(247); // wifi connected
            break;
        case 3:
            u8g2.write(248); //mqtt connected
            break;
        case 4:
            u8g2.write(121); //wifi failed
            break;
        default:
            u8g2.write(87); // disconected
    }

    if (send) {
        u8g2.sendBuffer();
    }
}

void showScale(bool send)
{
    u8g2.setFont(u8g2_font_tenstamps_mn);
    u8g2.setCursor(112,29);
    u8g2.print(state.scale);
    if (send) {
        u8g2.sendBuffer();
    }
}

void showVoltage(bool send)
{
    int offset = 0;
    int pre_offset = 0;
    int post_offset = 0;
    String value;
    u8g2.setFont(u8g2_font_bubble_tr);

    // calculate voltage
    state.voltage = state.adc_avg;
    for (int i=0; i<state.scale; i++) {
        state.voltage *= 10;
    }
    state.voltage /= state.adc_ratio;
    value = String(state.voltage/1000.0, 3);
    u8g2.setCursor(0,22);
//    u8g2.print(adc_now);

//*
    // strip zero
    if (value.charAt(0) == '0') {
        value = value.substring(1);
    }

    // fix character spacing and print
    for (int i=0; i<4; i++) {
        pre_offset = 0;
        switch (value.charAt(i)) {
            case '.':
               post_offset = 16;
                break;
             case '1':
                pre_offset = 8;
            default:
                post_offset = 28;
        }
        u8g2.setCursor(offset+pre_offset,22);
        u8g2.print(value.charAt(i));

        offset += post_offset;
    }
/* */

    if (send) {
        u8g2.sendBuffer();
    }
}

void showMessage(int message)
{
    u8g2.setFont(u8g2_font_bubble_tr);
    u8g2.setCursor(0,22);
    u8g2.print(message);
    u8g2.sendBuffer();
}



