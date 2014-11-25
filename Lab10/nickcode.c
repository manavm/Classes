		{"who",						CMD_who,
									"display the IP address of your client and the address you are using for the server"};
		{"server",				CMD_server,
									"specify IP address of the server"};
		{"test"						CMD_test,
								"send 100 packets of data to the server"};
int
CMD_who(int argc, char **argv){
	  SlPingStartCommand_t PingParams;
    SlPingReport_t Report;
    _NetCfgIpV4Args_t ipV4;

    unsigned char len = sizeof(_NetCfgIpV4Args_t);;
    unsigned char IsDHCP = 0;

    /* Read the IP parameter */
    sl_NetCfgGet(SL_IPV4_STA_P2P_CL_GET_INFO,&IsDHCP,&len,
            (unsigned char *)&ipV4);

	/*Method one to Look At the Send Ip*/
	Int2Str(IP_ADDR,(char*)&uBuf[0]); // [2] to [7] is 6 digit number
	UARTprintf(" %s ",uBuf);
	/*Method two to Look at the Send Ip*/
	UARTprintf(" Send IP: %d.%d.%d.%d  Port: %d\n\n",
      SL_IPV4_BYTE(IP_ADDR,3), SL_IPV4_BYTE(IP_ADDR,2), 
      SL_IPV4_BYTE(IP_ADDR,1), SL_IPV4_BYTE(IP_ADDR,0),PORT_NUM);
}
int
CMD_server(int argc, char **argv){

}

int
CMD_test(int argc, char **argv){
	data = 1;
    while(Status > 0){
      UARTprintf("\nSending 100 packets ...");
      uBuf[0] = 'test';   // defines this as an analog data type
      uBuf[1] = '='; 
      data = 1
      Int2Str(data,(char*)&uBuf[2]); // [2] to [7] is 6 digit number
      UARTprintf(" %s ",uBuf);
      if( SockID < 0 ){
        UARTprintf("SockIDerror ");
        Status = -1; // error
      }else{
        LED_Toggle();
        Status = sl_SendTo(SockID, uBuf, BUF_SIZE, 0,
                           (SlSockAddr_t *)&Addr, AddrSize);
        if( Status <= 0 ){
          sl_Close(SockID);
          UARTprintf("SockIDerror %d ",Status);
        }else{
          UARTprintf("ok");
        }
      }
      ROM_SysCtlDelay(ROM_SysCtlClockGet() / 100); // 10ms
    data = data + 1;
#endif
			data >= 101;
			return 0;
		}
  }

}