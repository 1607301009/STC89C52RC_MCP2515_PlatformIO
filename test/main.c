
void E2_buf(uint8 isRead)
{
    uint8 Send_data[] = {
            // 波特率, 工作模式, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
            0x14, 0x05, 0x03, 0x00, 0x01, 0x05, 0x03, 0x00,
            // RXF0ID, 1 2 3   4 5    ExIDE   id
            0x1F, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0xFF,
            0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01,
            0x00, 0x00, 0x07, 0xff, 0x10, 0x00, 0x17, 0xFF,
            // RXM0ID 0 1
            0x9F, 0xFF, 0xFF, 0xFF, 0x9F, 0xFF, 0xFF, 0xFE};
    printf("E2_buf: %02X ", isRead);
    if (isRead == 1) {
        E2Read(Send_data, 0, 40);
        for (isRead = 0; isRead < 40; isRead++) {
            if (isRead % 8 == 0) {
                printf("\r\n");
            }
            if (isRead % 4 == 0) {
                printf("  ");
            }
            printf(" %02X ", Send_data[isRead]);
        }
    } else {
        E2Write(Send_data, 0, 8);
    }

    printf("\r\n E2 end\r\n");
}


void test_Get_ID_For_Array()
{
    uint8 Send_data[] = {
            // 波特率, 工作模式, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
            // RXF0ID, 1 2 3   4 5    ExIDE   id
            0xDF, 0x12, 0x34, 0x56, 0x1F, 0xFF, 0xFF, 0xFF,
            };

    printf("Now test %s: %d   --> ", __func__, __LINE__);
    uint32 ID = Get_ID_For_Array(Send_data, 0);
    if (ID == 0x1F123456) {
        printf("pass \r\n", ID);
    } else {
        printf("    Fail!!!!\r\n", ID);
    }
}




void test_Set_Array_For_ID()
{
    //    Set_Array_For_ID(uint8 *array, uint8 offset, uint32 ID, uint8 EXIDEr);
    uint8 Send_data[8];
    uint32 ID = 0xFE123456;

    printf("Now test %s: %d   --> ", __func__, __LINE__);

    Set_Array_For_ID(Send_data, 0, ID, 0);
    //    Set_Array_For_ID(Send_data, 4, ID, 3);
    if (Send_data[0] == 0x1E && Send_data[1] == 0x12 && Send_data[2] == 0x34 && Send_data[3] == 0x56) {
        printf("pass \r\n", ID);
    } else {
        printf("    Fail!!!!\r\n", ID);
        Print_array(Send_data, 8);
    }

}

void test_Get_ID_For_Buf()
{

}



