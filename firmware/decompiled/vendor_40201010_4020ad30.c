/*
 * Прошивка платы карта SmartKart v5.1 (ESP8266, D1 mini), версия 0.9.10.
 * Код производителя (0x40201010-0x4020ad30), декомпилированный Ghidra 12.2,
 * процессор Xtensa:LE:32, соглашение __call0. Это псевдо-C, он не собирается.
 *
 * Основа прошивки — открытый проект tretyakovsa/Sonoff_WiFi_switch (GPL-3.0);
 * картовая часть дописана производителем платы.
 *
 * Имена функций (setup, ws_event, throttle_tick_30ms ...) даны по разбору
 * 25.11.2026 — см. ai/03-proshivka.md. Остальные — как у Ghidra: FUN_<адрес>.
 * Пароли и адреса из образа вычищены: *_REDACTED. Значения — в закрытом
 * репозитории FireDrift_Access.
 */

/* ==== 40201070  FUN_40201070  size=25 ==== */

void FUN_40201070(undefined4 *param_1)

{
  *param_1 = PTR_PTR_4020106c;
  FUN_40215e1c(param_1 + 1);
  return;
}



/* ==== 4020108c  FUN_4020108c  size=20 ==== */

void FUN_4020108c(int param_1)

{
  FUN_4021678c(param_1 + 4);
  return;
}



/* ==== 402010a0  FUN_402010a0  size=61 ==== */

uint FUN_402010a0(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x20);
  uVar2 = 0;
  if (uVar1 < *(uint *)(param_1 + 0x18)) {
    uVar2 = *(uint *)(param_1 + 0x18) - uVar1;
    if (param_3 < uVar2) {
      uVar2 = param_3;
    }
    FUN_40229160(param_2,*(int *)(param_1 + 0x14) + uVar1,uVar2);
    *(uint *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + uVar2;
  }
  return uVar2;
}



/* ==== 4020111c  FUN_4020111c  size=46 ==== */

undefined4 * FUN_4020111c(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_4021703c(0x10);
  *puVar1 = PTR_PTR_4020106c;
  FUN_40216114(puVar1 + 1,param_1 + 4);
  return puVar1;
}



/* ==== 4020118c  FUN_4020118c  size=66 ==== */

void FUN_4020118c(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1[2];
  iVar2 = param_1[3];
  *param_1 = PTR_PTR_40201188;
  for (; iVar2 != iVar1; iVar1 = iVar1 + 0xc) {
    FUN_40215e1c(iVar1);
  }
  iVar1 = param_1[2];
  if (iVar1 != 0) {
    FUN_4022e918(iVar1,param_1[4] - iVar1);
  }
  return;
}



/* ==== 402011d0  FUN_402011d0  size=31 ==== */

void FUN_402011d0(undefined4 param_1)

{
  FUN_4020118c();
  FUN_4022e918(param_1,0x14);
  return;
}



/* ==== 402011f0  FUN_402011f0  size=31 ==== */

void FUN_402011f0(undefined4 param_1)

{
  FUN_40201070();
  FUN_4022e918(param_1,0x10);
  return;
}



/* ==== 40201220  FUN_40201220  size=62 ==== */

void FUN_40201220(undefined1 param_1,int param_2)

{
  if (param_2 == 1) {
    FUN_40214c40(PTR_DAT_40201034,PTR_s_web_Socket_disconnected_40201210);
  }
  else if (param_2 == 2) {
    FUN_40214c40(PTR_DAT_40201034,PTR_s_web_Socket_Connected_40201214);
    FUN_40211af8(PTR_DAT_4020121c,param_1,PTR_DAT_40201218);
  }
  return;
}



/* ==== 40201260  FUN_40201260  size=49 ==== */

void FUN_40201260(int param_1)

{
  FUN_40215e1c(param_1 + 0x1c);
  FUN_40215e1c(param_1 + 0x10);
  FUN_40215e1c(param_1 + 4);
  FUN_4022e918(param_1,0x834);
  return;
}



/* ==== 40201294  FUN_40201294  size=104 ==== */

void FUN_40201294(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  int iStack_2c;
  
  iVar1 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0xa4) <= iVar1) {
      return;
    }
    iVar2 = *(int *)(param_1 + 0xa8);
    iStack_2c = iVar1 * 0x18;
    uStack_30 = param_3;
    FUN_40216000(auStack_40,param_2);
    iVar2 = FUN_40216838(iVar1 * 0x18 + iVar2,auStack_40);
    FUN_40215e1c(auStack_40);
    if (iVar2 != 0) break;
    iVar1 = iVar1 + 1;
    param_3 = uStack_30;
  }
  FUN_4021614c(*(int *)(param_1 + 0xa8) + iStack_2c + 0xc,uStack_30);
  return;
}



/* ==== 40201300  FUN_40201300  size=53 ==== */

void FUN_40201300(undefined4 *param_1)

{
  *param_1 = PTR_PTR_402012fc;
  if ((int *)param_1[0xd] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0xd] + 4))();
  }
  FUN_402226a4(param_1 + 9);
  FUN_402226a4(param_1 + 5);
  FUN_4020118c(param_1);
  return;
}



/* ==== 40201338  FUN_40201338  size=31 ==== */

void FUN_40201338(undefined4 param_1)

{
  FUN_40201300();
  FUN_4022e918(param_1,0x3c);
  return;
}



/* ==== 4020135c  FUN_4020135c  size=96 ==== */

undefined4 FUN_4020135c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_40216b28(param_2,param_3,0);
  if (iVar1 == -1) {
    FUN_40216114(param_1,PTR_DAT_40201358);
  }
  else {
    iVar2 = FUN_402226bc(param_3);
    uVar3 = FUN_40216a98(param_2,param_4,iVar1 + iVar2);
    FUN_40216c00(param_1,param_2,iVar1 + iVar2,uVar3);
  }
  return param_1;
}



/* ==== 402013c0  FUN_402013c0  size=32 ==== */

int FUN_402013c0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x18);
  iVar1 = FUN_402226bc(*(undefined4 *)(param_1 + 0x14));
  if (-1 < iVar2) {
    iVar1 = iVar1 - iVar2;
  }
  return iVar1;
}



/* ==== 402013e0  FUN_402013e0  size=60 ==== */

void FUN_402013e0(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x18);
  if (iVar3 < 0) {
    FUN_40216e90(*(undefined4 *)(param_1 + 0x14),0,param_2);
  }
  else {
    uVar1 = FUN_402226bc(*(undefined4 *)(param_1 + 0x14));
    uVar2 = iVar3 + param_2;
    if (uVar1 < uVar2) {
      uVar2 = uVar1;
    }
    *(uint *)(param_1 + 0x18) = uVar2;
  }
  return;
}



/* ==== 40201420  FUN_40201420  size=65 ==== */

undefined4 * FUN_40201420(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x18);
  puVar3 = *(undefined4 **)(param_1 + 0x14);
  if (iVar4 < 0) {
    puVar2 = puVar3;
    if ((*(byte *)((int)puVar3 + 0xb) & 0x80) != 0) {
      puVar2 = (undefined4 *)*puVar3;
    }
  }
  else {
    iVar1 = FUN_402226bc(puVar3);
    puVar2 = (undefined4 *)0x0;
    if (iVar4 < iVar1) {
      if ((*(byte *)((int)puVar3 + 0xb) & 0x80) != 0) {
        puVar3 = (undefined4 *)*puVar3;
      }
      puVar2 = (undefined4 *)((int)puVar3 + iVar4);
    }
  }
  return puVar2;
}



/* ==== 40201464  FUN_40201464  size=32 ==== */

int FUN_40201464(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x18);
  iVar1 = FUN_402226bc(*(undefined4 *)(param_1 + 0x14));
  if (-1 < iVar2) {
    iVar1 = iVar1 - iVar2;
  }
  return iVar1;
}



/* ==== 40201484  FUN_40201484  size=59 ==== */

undefined4 FUN_40201484(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = *(undefined4 *)(param_1 + 0x14);
  iVar3 = *(int *)(param_1 + 0x18);
  iVar1 = FUN_402226bc(uVar2);
  if (iVar3 < 0) {
    if (iVar1 == 0) {
      return 0xffffffff;
    }
    iVar3 = 0;
  }
  else if (iVar1 <= iVar3) {
    return 0xffffffff;
  }
  uVar2 = FUN_40216a64(uVar2,iVar3);
  return uVar2;
}



/* ==== 402014c4  FUN_402014c4  size=132 ==== */

uint FUN_402014c4(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar3 = *(undefined4 **)(param_1 + 0x14);
  iVar4 = *(int *)(param_1 + 0x18);
  uVar1 = FUN_402226bc(puVar3);
  if (iVar4 < 0) {
    uVar2 = param_3;
    if (uVar1 < param_3) {
      uVar2 = uVar1;
    }
    if ((*(byte *)((int)puVar3 + 0xb) & 0x80) != 0) {
      puVar3 = (undefined4 *)*puVar3;
    }
    (*(code *)PTR_FUN_402014c0)(param_2,puVar3,uVar2);
    FUN_40216e90(*(undefined4 *)(param_1 + 0x14),0,uVar2);
  }
  else {
    uVar2 = 0;
    if (iVar4 < (int)uVar1) {
      uVar2 = uVar1 - iVar4;
      if (param_3 < uVar1 - iVar4) {
        uVar2 = param_3;
      }
      if ((*(byte *)((int)puVar3 + 0xb) & 0x80) != 0) {
        puVar3 = (undefined4 *)*puVar3;
      }
      (*(code *)PTR_FUN_402014c0)(param_2,(int)puVar3 + iVar4,uVar2);
      *(uint *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + uVar2;
    }
  }
  return uVar2;
}



/* ==== 4020154c  FUN_4020154c  size=85 ==== */

undefined4 FUN_4020154c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = *(undefined4 *)(param_1 + 0x14);
  iVar3 = *(int *)(param_1 + 0x18);
  iVar1 = FUN_402226bc(uVar4);
  uVar2 = 0xffffffff;
  if (iVar3 < 0) {
    if (iVar1 != 0) {
      uVar2 = FUN_40216a64(uVar4,0);
      FUN_40216e90(*(undefined4 *)(param_1 + 0x14),0,1);
    }
  }
  else if (iVar3 < iVar1) {
    *(int *)(param_1 + 0x18) = iVar3 + 1;
    uVar2 = FUN_40216a64(uVar4,iVar3);
  }
  return uVar2;
}



/* ==== 402015b8  FUN_402015b8  size=23 ==== */

byte FUN_402015b8(void)

{
  byte bVar1;
  
  bVar1 = FUN_4021678c();
  return bVar1 ^ 1;
}



/* ==== 402015d0  FUN_402015d0  size=41 ==== */

undefined4 FUN_402015d0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 auStack_20 [24];
  
  FUN_40216338(auStack_20);
  uVar1 = FUN_40216988(param_1,auStack_20);
  FUN_40215e1c(auStack_20);
  return uVar1;
}



/* ==== 402015fc  FUN_402015fc  size=41 ==== */

undefined4 FUN_402015fc(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 auStack_20 [24];
  
  FUN_40216000(auStack_20);
  uVar1 = FUN_402169c4(param_1,auStack_20);
  FUN_40215e1c(auStack_20);
  return uVar1;
}



/* ==== 40201628  FUN_40201628  size=45 ==== */

undefined4 FUN_40201628(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  
  if ((*(byte *)(param_2 + 0xb) & 0x80) == 0) {
    uVar1 = *(uint *)(param_2 + 8) >> 0x18 & 0x7f;
  }
  else {
    uVar1 = (uint)*(ushort *)(param_2 + 6);
  }
  FUN_40216c00(param_1,param_2,param_3,uVar1);
  return param_1;
}



/* ==== 40201658  FUN_40201658  size=55 ==== */

void FUN_40201658(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [24];
  
  FUN_40216000(auStack_24);
  FUN_40216000(auStack_30,param_3);
  FUN_40216c68(param_1,auStack_24,auStack_30);
  FUN_40215e1c(auStack_30);
  FUN_40215e1c(auStack_24);
  return;
}



/* ==== 40201694  FUN_40201694  size=53 ==== */

void FUN_40201694(undefined4 param_1,int *param_2)

{
  undefined2 uVar1;
  
  if ((*(byte *)((int)param_2 + 0xb) & 0x80) != 0) {
    param_2 = (int *)*param_2;
  }
  uVar1 = (*(code *)PTR_FUN_40201690)(param_2);
  FUN_402148a8(param_1,param_2,uVar1);
  return;
}



/* ==== 402016cc  FUN_402016cc  size=25 ==== */

void FUN_402016cc(undefined4 *param_1)

{
  *param_1 = PTR_PTR_4020106c;
  FUN_40216000(param_1 + 1);
  return;
}



/* ==== 402016f0  FUN_402016f0  size=61 ==== */

undefined * FUN_402016f0(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  puVar2 = PTR_DAT_402016ec;
  puVar1 = PTR_DAT_402016e8;
  memw();
  if ((*PTR_DAT_402016e8 == '\0') && (iVar3 = FUN_40223668(PTR_DAT_402016e8), iVar3 != 0)) {
    *(undefined4 *)puVar2 = 0;
    *(undefined4 *)(puVar2 + 4) = 0;
    FUN_40223688(puVar1);
  }
  return puVar2;
}



/* ==== 40201738  FUN_40201738  size=61 ==== */

undefined * FUN_40201738(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  puVar2 = PTR_DAT_40201734;
  puVar1 = PTR_DAT_40201730;
  memw();
  if ((*PTR_DAT_40201730 == '\0') && (iVar3 = FUN_40223668(PTR_DAT_40201730), iVar3 != 0)) {
    *(undefined4 *)puVar2 = 0;
    *(undefined4 *)(puVar2 + 4) = 0;
    FUN_40223688(puVar1);
  }
  return puVar2;
}



/* ==== 40201788  rc_detect_noise_on_gpio  size=121 ==== */

bool rc_detect_noise_on_gpio(undefined1 param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = DAT_40201778;
  do {
    iVar2 = (*(code *)PTR_FUN_40201784)(param_1);
    puVar1 = PTR_DAT_40201034;
    if (iVar2 == 0) {
      iVar3 = iVar3 + 1;
    }
    else {
      iVar5 = iVar5 + 1;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  FUN_40214ba0(PTR_DAT_40201034,PTR_s_ones__4020177c);
  FUN_40214e04(puVar1,iVar5,10);
  FUN_40214ba0(puVar1,PTR_s_zeros__40201780);
  FUN_40214ddc(puVar1,iVar3,10);
  return 1000 < iVar5 && 1000 < iVar3;
}



/* ==== 40201814  FUN_40201814  size=134 ==== */

int FUN_40201814(void)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  puVar1 = PTR_DAT_40201808;
  if (*PTR_DAT_40201804 == '\0') {
    FUN_40214c40(PTR_DAT_40201034,PTR_s_no_data_40201810);
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_40212ce4(PTR_DAT_40201808);
    if (iVar2 == 0) {
      iVar2 = *(int *)PTR_DAT_4020180c;
      if (iVar2 != 0) {
        *(undefined4 *)PTR_DAT_4020180c = 0;
      }
    }
    else {
      uVar3 = FUN_40212d04(puVar1);
      iVar2 = FUN_40212d10(puVar1);
      iVar4 = FUN_40212d20(puVar1);
      if (((iVar4 == 1) && (iVar2 == 0x18)) && (*(int *)PTR_DAT_4020180c == 0)) {
        *(undefined4 *)PTR_DAT_4020180c = uVar3;
      }
      FUN_40212cf8(puVar1);
      iVar2 = 0;
    }
  }
  return iVar2;
}



/* ==== 402018a4  gpio16_pulse_tick  size=65 ==== */

void gpio16_pulse_tick(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_4020189c;
  if ((*PTR_DAT_40201804 != '\0') && (*(int *)PTR_DAT_4020189c != 0)) {
    (*(code *)PTR_FUN_402018a0)(0x10,1);
    FUN_4021836c(0x32);
    (*(code *)PTR_FUN_402018a0)(0x10,0);
    *(int *)puVar1 = *(int *)puVar1 + -1;
  }
  return;
}



/* ==== 402018f4  start_inter_1s_ticker  size=47 ==== */

void start_inter_1s_ticker(void)

{
  undefined1 auStack_20 [8];
  undefined *puStack_18;
  undefined *puStack_14;
  
  puStack_14 = PTR_FUN_402018e8;
  puStack_18 = PTR_LAB_402018ec;
  FUN_4020faf4(PTR_DAT_402018f0,1,1000,auStack_20,0);
  FUN_402226a4(auStack_20);
  return;
}



/* ==== 40201924  time_now  size=20 ==== */

void time_now(void)

{
  FUN_4021977c(0);
  return;
}



/* ==== 40201940  FUN_40201940  size=85 ==== */

undefined4 FUN_40201940(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_30 [16];
  undefined8 auStack_20 [3];
  
  auStack_20[0] = FUN_4021977c(0);
  FUN_40216000(param_1,PTR_DAT_40201938);
  uVar1 = FUN_40225af4(auStack_20);
  FUN_4021646c(param_1,uVar1);
  iVar2 = FUN_40216ad8(param_1,PTR_s___3ffe9024_4_4020193c,0);
  FUN_40216c00(auStack_30,param_1,iVar2 + -2,iVar2 + 6);
  FUN_4021612c(param_1,auStack_30);
  FUN_40215e1c(auStack_30);
  return param_1;
}



/* ==== 402019a0  FUN_402019a0  size=131 ==== */

undefined4 FUN_402019a0(undefined4 param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [12];
  undefined8 uStack_18;
  
  uStack_18 = FUN_4021977c(0);
  puVar1 = PTR_DAT_40201938;
  FUN_40216000(param_1,PTR_DAT_40201938);
  uVar2 = FUN_40225af4(&uStack_18);
  FUN_4021646c(param_1,uVar2);
  FUN_40216000(auStack_30,PTR_DAT_40201998);
  iVar3 = FUN_40216bcc(param_1,auStack_30);
  FUN_40215e1c(auStack_30);
  FUN_40216c00(auStack_24,param_1,iVar3 + -8,iVar3 + 1);
  FUN_40216000(auStack_30,puVar1);
  FUN_40216c68(param_1,auStack_24,auStack_30);
  FUN_40215e1c(auStack_30);
  FUN_40201658(param_1,PTR_s__3ffe978f_0x17_4020199c,puVar1);
  FUN_40215e1c(auStack_24);
  return param_1;
}



/* ==== 40201a3c  FUN_40201a3c  size=167 ==== */

void FUN_40201a3c(int param_1)

{
  undefined *puVar1;
  int iVar2;
  longlong lVar3;
  undefined1 auStack_20 [16];
  
  iVar2 = FUN_4020b534(PTR_DAT_40201a24);
  if (iVar2 == 3) {
    FUN_402197d4(param_1 * 0xe10,0,PTR_s_pool_ntp_org_3ffe89c2_3_40201a2c,
                 PTR_s_ru_pool_ntp_org_40201a28);
    puVar1 = PTR_DAT_40201034;
    iVar2 = 0;
    FUN_40214c40(PTR_DAT_40201034,PTR_s_Waiting_for_time_40201a30);
    while ((lVar3 = FUN_4021977c(0), iVar2 != 10 && (lVar3 == 0))) {
      FUN_40214ba0(puVar1,PTR_DAT_40201a34);
      iVar2 = iVar2 + 1;
      FUN_4021836c(1000);
    }
    FUN_40214c40(puVar1,PTR_DAT_40201938);
    FUN_40214c40(puVar1,PTR_s_ITime_Ready__40201a38);
    FUN_40201940(auStack_20);
    FUN_40214c0c(puVar1,auStack_20);
    FUN_40215e1c(auStack_20);
    FUN_402019a0(auStack_20);
    FUN_40214c0c(puVar1,auStack_20);
    FUN_40215e1c(auStack_20);
  }
  return;
}



/* ==== 40201af4  ws_server_setup  size=54 ==== */

void ws_server_setup(void)

{
  undefined *puVar1;
  undefined *local_20 [2];
  undefined *puStack_18;
  undefined *puStack_14;
  
  puVar1 = PTR_DAT_4020121c;
  FUN_40212668(PTR_DAT_4020121c);
  local_20[0] = PTR_FUN_40201ae8;
  puStack_14 = PTR_FUN_40201aec;
  puStack_18 = PTR_LAB_40201af0;
  FUN_402126e0(puVar1,local_20);
  FUN_402226a4(local_20);
  return;
}



/* ==== 40201b54  ws_client_begin  size=328 ==== */

void ws_client_begin(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *local_70 [2];
  undefined *puStack_68;
  undefined *puStack_64;
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [12];
  uint uStack_30;
  
  puVar1 = PTR_DAT_40201034;
  FUN_40214bcc(PTR_DAT_40201034);
  puVar3 = PTR_DAT_40201b30;
  puVar2 = PTR_DAT_40201b2c;
  FUN_40216114(auStack_54,PTR_DAT_40201b30 + (uint)(byte)*PTR_DAT_40201b2c * 0xc);
  uStack_30 = (uint)*(ushort *)(PTR_DAT_40201b34 + (uint)(byte)*puVar2 * 2);
  FUN_40216114(auStack_60,PTR_DAT_40201b38 + (uint)(byte)*puVar2 * 0xc);
  FUN_40216000(local_70,PTR_s_arduino_40201b3c);
  puVar4 = PTR_DAT_40201b40;
  FUN_40210a44(PTR_DAT_40201b40,auStack_54,uStack_30,auStack_60,local_70);
  FUN_40215e1c(local_70);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  FUN_402166bc(auStack_3c,PTR_s_WS_connect_to_40201b44,puVar3 + (uint)(byte)*puVar2 * 0xc);
  FUN_4021646c(auStack_3c,PTR_s___3ffe9024_4_4020193c);
  FUN_402160bc(auStack_48,auStack_3c);
  FUN_40216290(auStack_54,*(undefined2 *)(PTR_DAT_40201b34 + (uint)(byte)*puVar2 * 2),10);
  FUN_40216644(auStack_60,auStack_48,auStack_54);
  FUN_402163d0(auStack_60,PTR_DAT_40201b38 + (uint)(byte)*puVar2 * 0xc);
  FUN_402160bc(local_70,auStack_60);
  FUN_40214c0c(puVar1,local_70);
  FUN_40215e1c(local_70);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  FUN_40215e1c(auStack_48);
  FUN_40215e1c(auStack_3c);
  local_70[0] = PTR_FUN_40201b48;
  puStack_64 = PTR_LAB_40201b4c;
  puStack_68 = PTR_LAB_40201b50;
  FUN_40210a74(puVar4,local_70);
  FUN_402226a4(local_70);
  FUN_40222e80(puVar4,5000);
  FUN_40211704(puVar4,15000,3000,2);
  return;
}



/* ==== 40201ca0  FUN_40201ca0  size=38 ==== */

void FUN_40201ca0(undefined4 *param_1)

{
  *param_1 = PTR_PTR_40201c9c;
  FUN_402226f4(param_1 + 9);
  FUN_402226f4(param_1 + 6);
  return;
}



/* ==== 40201cdc  FUN_40201cdc  size=100 ==== */

undefined4 FUN_40201cdc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined1 auStack_50 [44];
  undefined1 auStack_24 [24];
  
  FUN_402166bc(auStack_24,PTR_s___3ffe96af_0xe_40201cc8,param_2);
  FUN_402138b4(auStack_50,PTR_DAT_40201cd0,auStack_24,PTR_DAT_40201ccc);
  FUN_40215e1c(auStack_24);
  iVar1 = FUN_40223178(auStack_50);
  puVar2 = PTR_s_Failed_to_open_config_file_40201cd4;
  if (iVar1 != 0) {
    FUN_40223550(auStack_50,param_3);
    FUN_40213968(auStack_50);
    puVar2 = PTR_s_Write_sucsses_40201cd8;
  }
  FUN_40216000(param_1,puVar2);
  FUN_40201ca0(auStack_50);
  return param_1;
}



/* ==== 40201d48  save_localdrives_json  size=71 ==== */

void save_localdrives_json(void)

{
  undefined *puVar1;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [32];
  
  FUN_40216000(auStack_28,PTR_s_localdrives_json_40201d40);
  puVar1 = PTR_DAT_40201d44;
  FUN_40216114(auStack_34,PTR_DAT_40201d44);
  FUN_40201cdc(auStack_40,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40214c0c(PTR_DAT_40201034,puVar1);
  return;
}



/* ==== 40201d98  save_reboots_json  size=57 ==== */

void save_reboots_json(void)

{
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [36];
  
  FUN_40216000(auStack_28,PTR_s_reboots_json_40201d90);
  FUN_40216114(auStack_34,PTR_DAT_40201d94);
  FUN_40201cdc(auStack_40,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  return;
}



/* ==== 40201ddc  FUN_40201ddc  size=57 ==== */

void FUN_40201ddc(void)

{
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [36];
  
  FUN_40216000(auStack_28,PTR_s_config_json_40201dd4);
  FUN_40216114(auStack_34,PTR_DAT_40201dd8);
  FUN_40201cdc(auStack_40,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  return;
}



/* ==== 40201e24  FUN_40201e24  size=135 ==== */

undefined4 FUN_40201e24(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  undefined1 auStack_50 [44];
  undefined1 auStack_24 [24];
  
  FUN_402166bc(auStack_24,PTR_s___3ffe96af_0xe_40201cc8,param_2);
  FUN_402138b4(auStack_50,PTR_DAT_40201cd0,auStack_24,PTR_s_r_3ffe959f_0xa_40201e18);
  FUN_40215e1c(auStack_24);
  iVar1 = FUN_40223178(auStack_50);
  puVar3 = PTR_s_Failed_40201e1c;
  if (iVar1 != 0) {
    uVar2 = FUN_4022315c(auStack_50,PTR_s_Failed_40201e1c);
    if (uVar2 <= param_3) {
      FUN_40213634(auStack_24,auStack_50);
      FUN_40213968(auStack_50);
      FUN_402160bc(param_1,auStack_24);
      FUN_40215e1c(auStack_24);
      goto LAB_40201e99;
    }
    FUN_40213968(auStack_50);
    puVar3 = PTR_s_Large_40201e20;
  }
  FUN_40216000(param_1,puVar3);
LAB_40201e99:
  FUN_40201ca0(auStack_50);
  return param_1;
}



/* ==== 40201eb0  FUN_40201eb0  size=106 ==== */

void FUN_40201eb0(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [16];
  
  FUN_40216114(auStack_40,param_1);
  FUN_40201e24(auStack_1c,auStack_40,0x1000);
  FUN_40215e1c(auStack_40);
  FUN_402163d0(auStack_1c,param_2);
  FUN_40216114(auStack_28,param_1);
  FUN_40216114(auStack_34,auStack_1c);
  FUN_40201cdc(auStack_40,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40215e1c(auStack_1c);
  return;
}



/* ==== 40201f28  raceslist_write_and_send  size=156 ==== */

void raceslist_write_and_send(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [20];
  
  puVar1 = PTR_s_raceslist_txt_40201f1c;
  FUN_40216000(auStack_28,PTR_s_raceslist_txt_40201f1c);
  FUN_40201e24(auStack_34,auStack_28,0x1000);
  uVar2 = FUN_402165e0(auStack_34,0,PTR_s___Command___RacesList___Data____40201f20);
  FUN_402160bc(auStack_40,uVar2);
  FUN_4021646c(auStack_40,PTR_DAT_40201f24);
  FUN_402160bc(auStack_1c,auStack_40);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40210b58(PTR_DAT_40201b40,auStack_1c);
  FUN_40214c0c(PTR_DAT_40201034,auStack_1c);
  FUN_40216000(auStack_28,puVar1);
  FUN_40216000(auStack_34,PTR_DAT_40201938);
  FUN_40201cdc(auStack_40,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40215e1c(auStack_1c);
  return;
}



/* ==== 402020f4  FUN_402020f4  size=41 ==== */

void FUN_402020f4(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0xc))(param_1,param_3);
  if (iVar1 != 0) {
    (*(code *)PTR_FUN_402020f0)(param_1 + 9);
  }
  return;
}



/* ==== 40202120  FUN_40202120  size=50 ==== */

int FUN_40202120(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 8))(param_1,param_3,param_4);
  if (iVar1 != 0) {
    (*(code *)PTR_FUN_402020f0)(param_1 + 5);
  }
  return iVar1;
}



/* ==== 40202154  FUN_40202154  size=133 ==== */

void FUN_40202154(int param_1,int *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [28];
  
  FUN_4022272c(auStack_30,param_4);
  FUN_4022272c(auStack_40,param_5);
  puVar1 = (undefined4 *)FUN_4021703c(0x3c);
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  *puVar1 = PTR_PTR_402012fc;
  FUN_4022272c(puVar1 + 5,auStack_30);
  FUN_4022272c(puVar1 + 9,auStack_40);
  uVar2 = (**(code **)(*param_2 + 8))(param_2);
  puVar1[0xd] = uVar2;
  iVar3 = *(int *)(param_1 + 0x68);
  puVar1[0xe] = param_3;
  if (iVar3 == 0) {
    *(undefined4 **)(param_1 + 100) = puVar1;
  }
  else {
    *(undefined4 **)(iVar3 + 4) = puVar1;
  }
  *(undefined4 **)(param_1 + 0x68) = puVar1;
  FUN_402226a4(auStack_40);
  FUN_402226a4(auStack_30);
  return;
}



/* ==== 402021dc  FUN_402021dc  size=69 ==== */

void FUN_402021dc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  
  uStack_20 = param_3;
  FUN_4022272c(auStack_30,param_4);
  FUN_4022272c(auStack_40,param_1 + 0x7c);
  FUN_40202154(param_1,param_2,uStack_20,auStack_30,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_402226a4(auStack_30);
  return;
}



/* ==== 40202224  FUN_40202224  size=104 ==== */

undefined4 FUN_40202224(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < *(int *)(param_1 + 0x9c); iVar2 = iVar2 + 1) {
    iVar1 = FUN_4021678c(iVar2 * 0x18 + *(int *)(param_1 + 0xa0),param_2);
    if (iVar1 != 0) {
      return 1;
    }
  }
  iVar2 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x8c) + *(int *)(param_1 + 0x94) <= iVar2) {
      return 0;
    }
    iVar1 = FUN_4021678c(iVar2 * 0x18 + *(int *)(param_1 + 0x90),param_2);
    if (iVar1 != 0) break;
    iVar2 = iVar2 + 1;
  }
  return 1;
}



/* ==== 40202300  FUN_40202300  size=249 ==== */

undefined4 FUN_40202300(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined1 auStack_20 [16];
  
  FUN_40216000(auStack_20,PTR_s_download_40202290);
  iVar1 = FUN_40202224(PTR_DAT_40201fcc,auStack_20);
  FUN_40215e1c(auStack_20);
  puVar2 = PTR_s_application_octet_stream_40202294;
  if (iVar1 == 0) {
    iVar1 = FUN_402015fc(param_2,PTR_s__htm_3ffe8c4a_5_40202298);
    if ((iVar1 == 0) && (iVar1 = FUN_402015fc(param_2,PTR_s__html_402022a0), iVar1 == 0)) {
      iVar1 = FUN_402015fc(param_2,PTR_s__json_3ffe8ca9_6_402022a4);
      puVar2 = PTR_s_application_json_402022a8;
      if (iVar1 == 0) {
        iVar1 = FUN_402015fc(param_2,PTR_DAT_402022ac);
        puVar2 = PTR_s_text_css_402022b0;
        if (iVar1 == 0) {
          iVar1 = FUN_402015fc(param_2,PTR_DAT_402022b4);
          puVar2 = PTR_s_application_javascript_402022b8;
          if (iVar1 == 0) {
            iVar1 = FUN_402015fc(param_2,PTR_DAT_402022bc);
            puVar2 = PTR_s_image_png_402022c0;
            if (iVar1 == 0) {
              iVar1 = FUN_402015fc(param_2,PTR_DAT_402022c4);
              puVar2 = PTR_s_image_gif_402022c8;
              if (iVar1 == 0) {
                iVar1 = FUN_402015fc(param_2,PTR_DAT_402022cc);
                puVar2 = PTR_s_image_jpeg_402022d0;
                if (iVar1 == 0) {
                  iVar1 = FUN_402015fc(param_2,PTR_DAT_402022d4);
                  puVar2 = PTR_s_image_x_icon_402022d8;
                  if (iVar1 == 0) {
                    iVar1 = FUN_402015fc(param_2,PTR_s__xml_3ffe9632_0xb_402022dc);
                    puVar2 = PTR_s_text_xml_402022e0;
                    if (iVar1 == 0) {
                      iVar1 = FUN_402015fc(param_2,PTR_DAT_402022e4);
                      puVar2 = PTR_s_application_x_pdf_402022e8;
                      if (iVar1 == 0) {
                        iVar1 = FUN_402015fc(param_2,PTR_DAT_402022ec);
                        puVar2 = PTR_s_application_x_zip_402022f0;
                        if (iVar1 == 0) {
                          iVar1 = FUN_402015fc(param_2,PTR_DAT_402022f4);
                          puVar2 = PTR_s_application_x_gzip_402022f8;
                          if (iVar1 == 0) {
                            puVar2 = PTR_s_text_plain_402022fc;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      puVar2 = PTR_s_text_html_4020229c;
    }
  }
  FUN_40216000(param_1,puVar2);
  return param_1;
}



/* ==== 402023fc  FUN_402023fc  size=123 ==== */

undefined * FUN_402023fc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    if (*(int *)(param_1 + 0x9c) <= iVar2) {
      iVar2 = 0;
      while( true ) {
        if (*(int *)(param_1 + 0x8c) + *(int *)(param_1 + 0x94) <= iVar2) {
          return PTR_DAT_40201358;
        }
        iVar1 = FUN_4021678c(iVar2 * 0x18 + *(int *)(param_1 + 0x90),param_2);
        if (iVar1 != 0) break;
        iVar2 = iVar2 + 1;
      }
      iVar1 = *(int *)(param_1 + 0x90);
LAB_40202459:
      return (undefined *)(iVar1 + iVar2 * 0x18 + 0xc);
    }
    iVar1 = FUN_4021678c(iVar2 * 0x18 + *(int *)(param_1 + 0xa0),param_2);
    if (iVar1 != 0) {
      iVar1 = *(int *)(param_1 + 0xa0);
      goto LAB_40202459;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}



/* ==== 40202478  FUN_40202478  size=49 ==== */

void FUN_40202478(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_20 [20];
  
  FUN_4022272c(auStack_20,param_3);
  FUN_402021dc(param_1,param_2,0,auStack_20);
  FUN_402226a4(auStack_20);
  return;
}



/* ==== 402024b0  FUN_402024b0  size=44 ==== */

void FUN_402024b0(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 8);
  while (piVar2 != (int *)0x0) {
    puVar1 = piVar2 + 1;
    piVar2 = (int *)*piVar2;
    *(undefined4 *)(param_1 + 0xc) = *puVar1;
    (*(code *)PTR_FUN_402024ac)();
  }
  return;
}



/* ==== 402024dc  FUN_402024dc  size=86 ==== */

int FUN_402024dc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0xa4) <= iVar3) {
      return 0;
    }
    iVar1 = FUN_40216838(iVar3 * 0x18 + *(int *)(param_1 + 0xa8),param_2);
    if ((iVar1 != 0) &&
       (iVar2 = FUN_402226bc(*(int *)(param_1 + 0xa8) + iVar3 * 0x18 + 0xc), iVar2 != 0)) break;
    iVar3 = iVar3 + 1;
  }
  return iVar1;
}



/* ==== 40202534  FUN_40202534  size=80 ==== */

undefined * FUN_40202534(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0xa4) <= iVar2) {
      return PTR_DAT_40201358;
    }
    iVar1 = FUN_40216838(iVar2 * 0x18 + *(int *)(param_1 + 0xa8),param_2);
    if (iVar1 != 0) break;
    iVar2 = iVar2 + 1;
  }
  return (undefined *)(*(int *)(param_1 + 0xa8) + iVar2 * 0x18 + 0xc);
}



/* ==== 402025d0  FUN_402025d0  size=1408 ==== */

int FUN_402025d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined1 auStack_170 [104];
  undefined1 auStack_108 [12];
  undefined1 auStack_fc [12];
  undefined1 auStack_f0 [12];
  undefined1 auStack_e4 [12];
  undefined1 auStack_d8 [12];
  undefined1 auStack_cc [12];
  undefined1 auStack_c0 [12];
  undefined1 auStack_b4 [12];
  undefined1 auStack_a8 [12];
  int aiStack_9c [2];
  int iStack_94;
  int aiStack_90 [2];
  int iStack_88;
  undefined1 auStack_84 [12];
  undefined1 auStack_78 [12];
  undefined1 auStack_6c [12];
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [12];
  undefined4 uStack_30;
  int iStack_2c;
  
  puVar1 = PTR_s_Authorization_40202588;
  uStack_30 = param_2;
  FUN_40216338(auStack_170,PTR_s_Authorization_40202588);
  iVar3 = FUN_402024dc(param_1,auStack_170);
  FUN_40215e1c(auStack_170);
  if (iVar3 == 0) {
    return 0;
  }
  FUN_40216338(auStack_170,puVar1);
  uVar4 = FUN_40202534(param_1,auStack_170);
  FUN_40216114(auStack_3c,uVar4);
  FUN_40215e1c(auStack_170);
  iVar3 = FUN_402015d0(auStack_3c,PTR_s_Digest_4020258c);
  puVar1 = PTR_DAT_40201938;
  if (iVar3 == 0) {
LAB_40202b28:
    FUN_4021614c(auStack_3c,puVar1);
    FUN_40215e1c(auStack_3c);
    return 0;
  }
  FUN_40201628(auStack_170,auStack_3c,7);
  FUN_4021612c(auStack_3c,auStack_170);
  FUN_40215e1c(auStack_170);
  FUN_40216338(auStack_170,PTR_s_username___40202590);
  FUN_4020135c(auStack_48,auStack_3c,auStack_170,0x22);
  FUN_40215e1c(auStack_170);
  iVar3 = FUN_402226bc(auStack_48);
  if (iVar3 != 0) {
    FUN_40216114(auStack_170,uStack_30);
    iVar3 = FUN_402015b8(auStack_48,auStack_170);
    FUN_40215e1c(auStack_170);
    if (iVar3 == 0) {
      FUN_40216338(auStack_170,PTR_s_realm___40202594);
      FUN_4020135c(auStack_54,auStack_3c,auStack_170,0x22);
      FUN_40215e1c(auStack_170);
      FUN_40216338(auStack_170,PTR_s_nonce___40202598);
      FUN_4020135c(auStack_60,auStack_3c,auStack_170,0x22);
      FUN_40215e1c(auStack_170);
      FUN_40216338(auStack_170,PTR_s_uri___4020259c);
      FUN_4020135c(auStack_6c,auStack_3c,auStack_170,0x22);
      FUN_40215e1c(auStack_170);
      FUN_40216338(auStack_170,PTR_s_response___402025a0);
      FUN_4020135c(auStack_78,auStack_3c,auStack_170,0x22);
      FUN_40215e1c(auStack_170);
      FUN_40216338(auStack_170,PTR_s_opaque___402025a4);
      FUN_4020135c(auStack_84,auStack_3c,auStack_170,0x22);
      FUN_40215e1c(auStack_170);
      iVar3 = FUN_402226bc(auStack_54);
      if ((((iVar3 == 0) || (iVar3 = FUN_402226bc(auStack_60), iVar3 == 0)) ||
          (iVar3 = FUN_402226bc(auStack_6c), iVar3 == 0)) ||
         (((iVar3 = FUN_402226bc(auStack_78), iVar3 == 0 ||
           (iVar3 = FUN_402226bc(auStack_84), iVar3 == 0)) ||
          ((iVar3 = FUN_402015b8(auStack_84,param_1 + 0xd8), iVar3 != 0 ||
           ((iVar3 = FUN_402015b8(auStack_60,param_1 + 0xcc), iVar3 != 0 ||
            (iVar3 = FUN_402015b8(auStack_54,param_1 + 0xe4), puVar2 = PTR_s_qop_auth_402025a8,
            iVar3 != 0)))))))) {
        FUN_4021614c(auStack_3c,puVar1);
        iVar3 = 0;
      }
      else {
        aiStack_9c[0] = iVar3;
        iStack_94 = iVar3;
        aiStack_90[0] = iVar3;
        iStack_88 = iVar3;
        iStack_2c = iVar3;
        iVar3 = FUN_40216ad8(auStack_3c,PTR_s_qop_auth_402025a8,0);
        if ((iVar3 != -1) ||
           (iVar3 = FUN_40216ad8(auStack_3c,PTR_s_qop__auth__402025b4,iStack_2c), iVar3 != -1)) {
          FUN_40216338(auStack_108,PTR_DAT_402025ac);
          FUN_4020135c(auStack_170,auStack_3c,auStack_108,0x2c);
          FUN_4021612c(aiStack_90,auStack_170);
          FUN_40215e1c(auStack_170);
          FUN_40215e1c(auStack_108);
          FUN_40216338(auStack_108,PTR_s_cnonce___402025b0);
          FUN_4020135c(auStack_170,auStack_3c,auStack_108,0x22);
          FUN_4021612c(aiStack_9c,auStack_170);
          FUN_40215e1c(auStack_170);
          FUN_40215e1c(auStack_108);
        }
        FUN_4021487c(auStack_170);
        iVar3 = *(int *)(param_1 + 0x44);
        puVar5 = PTR_DAT_402025b8;
        if ((((iVar3 != 1) && (puVar5 = PTR_s_POST__402025bc, iVar3 != 3)) &&
            (puVar5 = PTR_DAT_402025c0, iVar3 != 4)) &&
           (puVar5 = PTR_s_DELETE__402025c4, iVar3 != 6)) {
          puVar5 = PTR_DAT_402025c8;
        }
        FUN_40216338(auStack_fc,puVar5);
        FUN_402163d0(auStack_fc,auStack_6c);
        FUN_402160bc(auStack_108,auStack_fc);
        FUN_40201694(auStack_170,auStack_108);
        FUN_40215e1c(auStack_108);
        FUN_40215e1c(auStack_fc);
        FUN_402148c4(auStack_170);
        FUN_40214918(auStack_a8,auStack_170);
        FUN_4021487c(auStack_170);
        iVar3 = FUN_40216ad8(auStack_3c,puVar2,0);
        if ((iVar3 == -1) &&
           (iVar3 = FUN_40216ad8(auStack_3c,PTR_s_qop__auth__402025b4,0), iVar3 == -1)) {
          FUN_40216114(auStack_e4,param_3);
          FUN_4021649c(auStack_e4,0x3a);
          FUN_402163d0(auStack_e4,auStack_60);
          FUN_402160bc(auStack_f0,auStack_e4);
          FUN_4021649c(auStack_f0,0x3a);
          FUN_402160bc(auStack_fc,auStack_f0);
          FUN_402163d0(auStack_fc,auStack_a8);
          FUN_402160bc(auStack_108,auStack_fc);
          FUN_40201694(auStack_170,auStack_108);
          FUN_40215e1c(auStack_108);
          FUN_40215e1c(auStack_fc);
          FUN_40215e1c(auStack_f0);
          iVar3 = 0x8c;
        }
        else {
          FUN_40216114(auStack_b4,param_3);
          FUN_4021649c(auStack_b4,0x3a);
          FUN_402163d0(auStack_b4,auStack_60);
          FUN_402160bc(auStack_c0,auStack_b4);
          FUN_4021649c(auStack_c0,0x3a);
          FUN_402160bc(auStack_cc,auStack_c0);
          FUN_402163d0(auStack_cc,aiStack_90);
          FUN_402160bc(auStack_d8,auStack_cc);
          FUN_4021649c(auStack_d8,0x3a);
          FUN_402160bc(auStack_e4,auStack_d8);
          FUN_402163d0(auStack_e4,aiStack_9c);
          FUN_402160bc(auStack_f0,auStack_e4);
          FUN_402164e0(auStack_f0,PTR_s__auth__402025cc);
          FUN_402160bc(auStack_fc,auStack_f0);
          FUN_402163d0(auStack_fc,auStack_a8);
          FUN_402160bc(auStack_108,auStack_fc);
          FUN_40201694(auStack_170,auStack_108);
          FUN_40215e1c(auStack_108);
          FUN_40215e1c(auStack_fc);
          FUN_40215e1c(auStack_f0);
          FUN_40215e1c(auStack_e4);
          FUN_40215e1c(auStack_d8);
          FUN_40215e1c(auStack_cc);
          FUN_40215e1c(auStack_c0);
          iVar3 = 0xbc;
        }
        FUN_40215e1c(auStack_170 + iVar3);
        FUN_402148c4(auStack_170);
        FUN_40214918(auStack_108,auStack_170);
        iVar3 = FUN_4021678c(auStack_78,auStack_108);
        if (iVar3 == 0) {
          FUN_40215e1c(auStack_108);
          FUN_40215e1c(auStack_a8);
          FUN_40215e1c(aiStack_9c);
          FUN_40215e1c(aiStack_90);
          FUN_40215e1c(auStack_84);
          FUN_40215e1c(auStack_78);
          FUN_40215e1c(auStack_6c);
          FUN_40215e1c(auStack_60);
          FUN_40215e1c(auStack_54);
          FUN_40215e1c(auStack_48);
          goto LAB_40202b28;
        }
        FUN_4021614c(auStack_3c,puVar1);
        FUN_40215e1c(auStack_108);
        FUN_40215e1c(auStack_a8);
        FUN_40215e1c(aiStack_9c);
        FUN_40215e1c(aiStack_90);
      }
      FUN_40215e1c(auStack_84);
      FUN_40215e1c(auStack_78);
      FUN_40215e1c(auStack_6c);
      FUN_40215e1c(auStack_60);
      FUN_40215e1c(auStack_54);
      goto LAB_40202b13;
    }
  }
  FUN_4021614c(auStack_3c,puVar1);
  iVar3 = 0;
LAB_40202b13:
  FUN_40215e1c(auStack_48);
  FUN_40215e1c(auStack_3c);
  return iVar3;
}



/* ==== 40202b6c  FUN_40202b6c  size=624 ==== */

int FUN_40202b6c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int local_100 [2];
  byte bStack_f5;
  undefined1 auStack_98 [12];
  undefined1 auStack_8c [12];
  undefined1 auStack_80 [12];
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  undefined1 auStack_5c [12];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [20];
  undefined4 uStack_30;
  
  puVar1 = PTR_s_Authorization_40202588;
  piVar6 = local_100;
  uStack_30 = param_3;
  FUN_40216338(local_100,PTR_s_Authorization_40202588);
  iVar2 = FUN_402024dc(param_1,local_100);
  FUN_40215e1c(local_100);
  if (iVar2 == 0) {
    return 0;
  }
  FUN_40216338(local_100,puVar1);
  uVar3 = FUN_40202534(param_1,local_100);
  FUN_40216114(auStack_44,uVar3);
  FUN_40215e1c(local_100);
  iVar2 = FUN_402015d0(auStack_44,PTR_s_Basic_40202b58);
  if (iVar2 == 0) {
    iVar2 = FUN_402015d0(auStack_44,PTR_s_Digest_40202b64);
    if (iVar2 == 0) {
LAB_40202da0:
      FUN_4021614c(auStack_44,PTR_DAT_40201938);
      FUN_40215e1c(auStack_44);
      return 0;
    }
    FUN_40216338(local_100,PTR_s_realm___40202b68);
    FUN_4020135c(auStack_50,auStack_44,local_100,0x22);
    FUN_40215e1c(local_100);
    FUN_40216000(auStack_5c,param_2);
    FUN_40216000(auStack_68,uStack_30);
    FUN_4021487c(local_100);
    FUN_40216114(auStack_74,auStack_5c);
    FUN_4021649c(auStack_74,0x3a);
    FUN_402163d0(auStack_74,auStack_50);
    FUN_402160bc(auStack_80,auStack_74);
    FUN_4021649c(auStack_80,0x3a);
    FUN_402160bc(auStack_8c,auStack_80);
    FUN_402163d0(auStack_8c,auStack_68);
    FUN_402160bc(auStack_98,auStack_8c);
    FUN_40201694(local_100,auStack_98);
    FUN_40215e1c(auStack_98);
    FUN_40215e1c(auStack_8c);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
    FUN_402148c4(local_100);
    FUN_40214918(auStack_98,local_100);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40216000(local_100,param_2);
    iVar2 = FUN_402025d0(param_1,local_100,auStack_98);
    FUN_40215e1c(local_100);
    FUN_40215e1c(auStack_98);
    piVar6 = (int *)auStack_50;
  }
  else {
    FUN_40201628(local_100,auStack_44,6);
    FUN_4021612c(auStack_44,local_100);
    FUN_40215e1c(local_100);
    FUN_40216f38(auStack_44);
    iVar4 = (*(code *)PTR_FUN_40201690)(param_2);
    iVar5 = (*(code *)PTR_FUN_40201690)(uStack_30);
    uVar7 = iVar4 + iVar5 + 1U & 0xff;
    iVar4 = FUN_402170d8(uVar7 + 1,PTR_DAT_40202b5c);
    if (iVar4 == 0) {
      FUN_4021614c(auStack_44,PTR_DAT_40201938);
      iVar2 = 0;
      goto LAB_40202dba;
    }
    FUN_402274f0(iVar4,PTR_s__s__s_40202b60,param_2,uStack_30);
    FUN_402170ec(local_100,iVar4,uVar7,0);
    if (((bStack_f5 & 0x80) == 0) || (local_100[0] != 0)) {
      iVar5 = FUN_402168a4(auStack_44,local_100);
      if (iVar5 == 0) {
        FUN_4022e928(iVar4);
        FUN_40215e1c(local_100);
        goto LAB_40202da0;
      }
      FUN_4021614c(auStack_44,PTR_DAT_40201938);
      FUN_4022e928(iVar4);
    }
    else {
      FUN_4021614c(auStack_44,PTR_DAT_40201938);
      FUN_4022e928(iVar4);
      iVar2 = 0;
    }
  }
  FUN_40215e1c(piVar6);
LAB_40202dba:
  FUN_40215e1c(auStack_44);
  return iVar2;
}



/* ==== 40202de8  FUN_40202de8  size=138 ==== */

void FUN_40202de8(int param_1,undefined4 param_2,undefined4 param_3,char param_4)

{
  int iVar1;
  int iVar2;
  undefined4 local_30 [2];
  undefined4 uStack_28;
  undefined1 auStack_24 [20];
  
  FUN_40216114(auStack_24);
  FUN_402164e0(auStack_24,PTR_DAT_40202de0);
  FUN_402163d0(auStack_24,param_3);
  FUN_4021646c(auStack_24,PTR_s__3ffe978f_0x16_40202de4);
  param_1 = param_1 + 0xb0;
  if (param_4 == '\0') {
    FUN_402163d0(param_1,auStack_24);
  }
  else {
    local_30[0] = 0;
    uStack_28 = 0;
    iVar1 = FUN_402226bc(auStack_24);
    iVar2 = FUN_402226bc(param_1);
    FUN_40215f54(local_30,iVar1 + iVar2);
    FUN_402163d0(local_30,auStack_24);
    FUN_402163d0(local_30,param_1);
    FUN_4021612c(param_1,local_30);
    FUN_40215e1c(local_30);
  }
  FUN_40215e1c(auStack_24);
  return;
}



/* ==== 40202e74  FUN_40202e74  size=43 ==== */

void FUN_40202e74(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_4022275c();
  uVar1 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(param_2 + 8) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_2 + 0xc) = uVar1;
  return;
}



/* ==== 40202ea0  FUN_40202ea0  size=37 ==== */

void FUN_40202ea0(undefined4 param_1)

{
  undefined1 auStack_20 [24];
  
  FUN_4022272c(auStack_20);
  FUN_40202e74(auStack_20,param_1);
  FUN_402226a4(auStack_20);
  return;
}



/* ==== 40202f00  FUN_40202f00  size=348 ==== */

void FUN_40202f00(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  undefined *local_50;
  undefined1 auStack_4c [4];
  undefined *puStack_48;
  undefined *puStack_44;
  undefined1 auStack_40 [8];
  undefined *puStack_38;
  undefined *puStack_34;
  undefined1 auStack_30 [28];
  
  puVar1 = PTR_DAT_40201cd0;
  FUN_40223224(PTR_DAT_40201cd0);
  FUN_40213770(&local_50,puVar1,PTR_s___3ffe96af_0xe_40201cc8);
  while (iVar5 = FUN_402231e0(&local_50), iVar5 != 0) {
    FUN_40213708(auStack_40,&local_50);
    FUN_402231c4(&local_50);
    FUN_40215e1c(auStack_40);
  }
  FUN_402226f4(auStack_4c);
  FUN_402016cc(auStack_40,PTR_s__list_40202ec8);
  puVar4 = PTR_LAB_40202ed4;
  puVar3 = PTR_FUN_40202ed0;
  puVar2 = PTR_DAT_40201fcc;
  local_50 = PTR_FUN_40202ecc;
  puStack_44 = PTR_FUN_40202ed0;
  puStack_48 = PTR_LAB_40202ed4;
  FUN_402021dc(PTR_DAT_40201fcc,auStack_40,1,&local_50);
  FUN_402226a4(&local_50);
  FUN_40201070(auStack_40);
  puVar1 = PTR_s__edit_40201fc4;
  FUN_402016cc(auStack_40,PTR_s__edit_40201fc4);
  puStack_44 = PTR_FUN_40202ed8;
  puStack_48 = PTR_LAB_40202edc;
  FUN_402021dc(puVar2,auStack_40,1,&local_50);
  FUN_402226a4(&local_50);
  FUN_40201070(auStack_40);
  FUN_402016cc(auStack_40,puVar1);
  local_50 = PTR_FUN_40202ee0;
  puStack_44 = puVar3;
  puStack_48 = puVar4;
  FUN_402021dc(puVar2,auStack_40,4,&local_50);
  FUN_402226a4(&local_50);
  FUN_40201070(auStack_40);
  FUN_402016cc(auStack_40,puVar1);
  local_50 = PTR_FUN_40202ee4;
  puStack_44 = puVar3;
  puStack_48 = puVar4;
  FUN_402021dc(puVar2,auStack_40,6,&local_50);
  FUN_402226a4(&local_50);
  FUN_40201070(auStack_40);
  FUN_402016cc(auStack_30,puVar1);
  puStack_34 = PTR_LAB_40202ee8;
  puStack_38 = PTR_LAB_40202eec;
  local_50 = PTR_LAB_40202ef0;
  puStack_44 = puVar3;
  puStack_48 = puVar4;
  FUN_40202154(puVar2,auStack_30,3,auStack_40,&local_50);
  FUN_402226a4(&local_50);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  puStack_44 = PTR_FUN_40202ef4;
  puStack_48 = PTR_LAB_40202ef8;
  FUN_40202ea0(PTR_DAT_40202efc,&local_50);
  FUN_402226a4(&local_50);
  return;
}



/* ==== 4020305c  FUN_4020305c  size=30 ==== */

void FUN_4020305c(int param_1)

{
  FUN_40215e1c(param_1 + 0xc);
  FUN_40215e1c(param_1);
  return;
}



/* ==== 40203080  FUN_40203080  size=137 ==== */

void FUN_40203080(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(param_1 + 0xa8);
  if (iVar2 != 0) {
    iVar2 = *(int *)(iVar2 + -4) * 0x18 + iVar2;
    while (*(int *)(param_1 + 0xa8) != iVar2) {
      iVar2 = iVar2 + -0x18;
      FUN_4020305c(iVar2);
    }
    FUN_4022e938((int *)(iVar2 + -4),*(int *)(iVar2 + -4) * 0x18 + 4);
  }
  *(undefined4 *)(param_1 + 0xa4) = 2;
  puVar3 = (undefined4 *)FUN_40217074(0x34);
  *puVar3 = 2;
  FUN_40216338(puVar3 + 1,PTR_s_Authorization_40202588);
  puVar1 = PTR_DAT_40201358;
  FUN_40216114(puVar3 + 4,PTR_DAT_40201358);
  FUN_40216338(puVar3 + 7,PTR_s_If_None_Match_4020307c);
  FUN_40216114(puVar3 + 10,puVar1);
  *(undefined4 **)(param_1 + 0xa8) = puVar3 + 1;
  return;
}



/* ==== 4020310c  FUN_4020310c  size=257 ==== */

int FUN_4020310c(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int extraout_a3;
  int iVar4;
  int extraout_a4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iStack_40;
  int iStack_3c;
  uint uStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  
  iVar6 = 0;
  uVar7 = 0;
  iStack_30 = param_1;
LAB_40203128:
  do {
    iVar1 = FUN_40216a64(param_2,uVar7);
    if ((iVar1 == 0x26) || (iVar1 = FUN_40216a64(param_2,uVar7), iVar1 == 0x3b)) {
      uVar7 = uVar7 + 1;
      uVar2 = FUN_402226bc(param_2);
      if (uVar7 < uVar2) goto LAB_40203128;
    }
    iStack_28 = FUN_40216a98(param_2,0x3d,uVar7);
    iStack_2c = FUN_40216a98(param_2,0x26,uVar7);
    iVar1 = FUN_40216a98(param_2,0x3b,uVar7);
    if ((iStack_2c == -1) || ((iVar1 != -1 && (iVar1 < iStack_2c)))) {
      if (iStack_28 != -1) {
        iVar5 = iVar1;
        goto LAB_40203185;
      }
      if (iVar1 != -1) {
        goto LAB_40203199;
      }
      iVar1 = FUN_402226bc(param_2);
      iVar5 = iStack_28;
    }
    else {
      iVar1 = iStack_2c;
      iVar5 = iStack_2c;
      if (iStack_28 == -1) {
LAB_40203199:
        iVar5 = iVar1;
      }
      else {
LAB_40203185:
        if ((iStack_28 <= iVar5) || (iVar1 = iVar5, iVar5 == -1)) {
          iVar1 = iStack_28;
        }
      }
    }
    if ((int)uVar7 < iVar1) {
      iVar3 = iVar6 * 0x18 + *(int *)(iStack_30 + 0x90);
      iVar4 = iVar3 + 0xc;
      iStack_40 = iVar5;
      iStack_3c = iVar1;
      uStack_38 = uVar7;
      iStack_34 = iStack_28;
      if (*(int *)(param_3 + 8) == 0) {
        FUN_4022e958(0,iVar3,iVar4);
        iVar3 = extraout_a3;
        iVar4 = extraout_a4;
      }
      iStack_2c = iVar5;
      (**(code **)(param_3 + 0xc))
                (param_3,iVar3,iVar4,param_2,&iStack_34,&uStack_38,&iStack_3c,&iStack_40);
      iVar6 = iVar6 + 1;
      uVar7 = iStack_2c + 1;
      iVar5 = iStack_2c;
    }
    if (iVar5 == -1) {
      return iVar6;
    }
  } while( true );
}



/* ==== 40203224  FUN_40203224  size=192 ==== */

void FUN_40203224(int param_1,undefined4 param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  undefined1 auStack_40 [8];
  undefined *puStack_38;
  undefined *puStack_34;
  uint *puStack_30;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if (iVar2 != 0) {
    iVar2 = *(int *)(iVar2 + -4) * 0x18 + iVar2;
    while (*(int *)(param_1 + 0x90) != iVar2) {
      iVar2 = iVar2 + -0x18;
      FUN_4020305c(iVar2);
    }
    FUN_4022e938((int *)(iVar2 + -4),*(int *)(iVar2 + -4) * 0x18 + 4);
  }
  puStack_34 = PTR_LAB_40203210;
  puStack_38 = PTR_LAB_40203214;
  uVar3 = FUN_4020310c(param_1,param_2,auStack_40);
  *(undefined4 *)(param_1 + 0x8c) = uVar3;
  FUN_402226a4(auStack_40);
  iVar6 = *(int *)(param_1 + 0x8c);
  uVar7 = iVar6 + 1;
  iVar2 = -1;
  if (uVar7 <= DAT_40203218) {
    iVar2 = uVar7 * 0x18 + 4;
  }
  puVar4 = (uint *)FUN_40217074(iVar2);
  *puVar4 = uVar7;
  puVar5 = puVar4 + 1;
  for (; puVar1 = PTR_FUN_4020321c, -1 < iVar6; iVar6 = iVar6 + -1) {
    puStack_30 = puVar5;
    FUN_40222774(puVar5);
    puVar5 = puStack_30 + 6;
  }
  *(uint **)(param_1 + 0x90) = puVar4 + 1;
  puStack_34 = puVar1;
  puStack_38 = PTR_LAB_40203220;
  FUN_4020310c(param_1,param_2,auStack_40);
  FUN_402226a4(auStack_40);
  return;
}



/* ==== 40203304  FUN_40203304  size=1912 ==== */

uint FUN_40203304(int param_1,int *param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  int *piVar9;
  uint *puVar10;
  uint *puVar11;
  int iVar12;
  undefined1 auStack_b0 [12];
  undefined1 auStack_a4 [12];
  undefined4 auStack_98 [2];
  undefined4 uStack_90;
  undefined4 auStack_8c [2];
  undefined4 uStack_84;
  undefined4 auStack_80 [2];
  undefined4 uStack_78;
  undefined4 auStack_74 [2];
  undefined4 uStack_6c;
  undefined4 auStack_68 [2];
  undefined4 uStack_60;
  uint uStack_50;
  undefined4 *puStack_4c;
  byte *pbStack_48;
  undefined1 *puStack_44;
  uint uStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  uint *puStack_34;
  uint *puStack_30;
  uint uStack_2c;
  
  puVar2 = auStack_b0;
  auStack_68[0] = 0;
  uStack_60 = 0;
  uStack_2c = 1;
  iVar4 = 0;
  puStack_4c = param_3;
  uStack_38 = param_4;
  do {
    FUN_40214fec(auStack_b0,param_2,0xd);
    FUN_4021612c(auStack_68,auStack_b0);
    FUN_40215e1c(auStack_b0);
    iVar3 = FUN_402226bc(auStack_68);
    uStack_40 = 0;
    if (iVar3 == 0) {
      uStack_40 = uStack_2c;
    }
    uVar6 = 0;
    if (iVar4 != 2) {
      uVar6 = uStack_2c;
    }
    uStack_40 = uStack_40 & uVar6;
    iVar4 = iVar4 + 1;
  } while (uStack_40 != 0);
  FUN_40214fec(auStack_b0,param_2,10);
  FUN_40215e1c(auStack_b0);
  FUN_402166bc(auStack_b0,PTR_DAT_402032e4,puStack_4c);
  uStack_50 = FUN_4021678c(auStack_68,auStack_b0);
  FUN_40215e1c(auStack_b0);
  if (uStack_50 != 0) {
    iVar4 = *(int *)(param_1 + 0xa0);
    if (iVar4 != 0) {
      iVar4 = *(int *)(iVar4 + -4) * 0x18 + iVar4;
      while (*(int *)(param_1 + 0xa0) != iVar4) {
        iVar4 = iVar4 + -0x18;
        FUN_4020305c(iVar4);
      }
      FUN_4022e938((int *)(iVar4 + -4),*(int *)(iVar4 + -4) * 0x18 + 4);
    }
    puVar5 = (undefined4 *)FUN_40217074(0x304);
    puVar10 = puVar5 + 1;
    *puVar5 = 0x20;
    puStack_30 = puVar10;
    do {
      puStack_34 = puVar10;
      FUN_40222774(puVar10);
      puVar10 = puStack_34 + 6;
    } while (puVar5 + 0xc1 != puVar10);
    *(uint **)(param_1 + 0xa0) = puStack_30;
    *(undefined4 *)(param_1 + 0x9c) = 0;
    do {
      auStack_74[0] = 0;
      uStack_6c = 0;
      auStack_80[0] = 0;
      uStack_78 = 0;
      auStack_8c[0] = 0;
      uStack_84 = 0;
      auStack_98[0] = 0;
      uStack_90 = 0;
      FUN_40214fec(auStack_b0,param_2,0xd);
      FUN_4021612c(auStack_68,auStack_b0);
      FUN_40215e1c(auStack_b0);
      FUN_40214fec(auStack_b0,param_2,10);
      FUN_40215e1c(auStack_b0);
      uVar6 = FUN_402226bc(auStack_68);
      if (0x13 < uVar6) {
        FUN_40216c00(auStack_a4,auStack_68,0,0x13);
        FUN_40216338(auStack_b0,PTR_s_Content_Disposition_402032e8);
        uStack_50 = FUN_40216838(auStack_a4,auStack_b0);
        FUN_40215e1c(auStack_b0);
        FUN_40215e1c(auStack_a4);
        if ((uStack_50 != 0) && (iVar4 = FUN_40216a98(auStack_68,0x3d,0), iVar4 != -1)) {
          FUN_40201628(auStack_b0,auStack_68,iVar4 + 2);
          FUN_4021612c(auStack_74,auStack_b0);
          FUN_40215e1c(auStack_b0);
          iVar4 = FUN_40216a98(auStack_74,0x3d,0);
          if (iVar4 == -1) {
            iVar4 = FUN_402226bc(auStack_74);
            FUN_40216c00(auStack_b0,auStack_74,0,iVar4 + -1);
            FUN_4021612c(auStack_74,auStack_b0);
            FUN_40215e1c(auStack_b0);
            uVar6 = uStack_40;
          }
          else {
            iVar3 = FUN_402226bc(auStack_74);
            FUN_40216c00(auStack_b0,auStack_74,iVar4 + 2,iVar3 + -1);
            FUN_4021612c(auStack_98,auStack_b0);
            FUN_40215e1c(auStack_b0);
            uVar8 = FUN_40216a98(auStack_74,0x22,0);
            FUN_40216c00(auStack_b0,auStack_74,0,uVar8);
            FUN_4021612c(auStack_74,auStack_b0);
            FUN_40215e1c(auStack_b0);
            FUN_40216338(auStack_a4,PTR_DAT_402032ec);
            iVar4 = FUN_4021678c(auStack_98,auStack_a4);
            uVar6 = 0;
            if (iVar4 != 0) {
              FUN_40216338(auStack_b0,PTR_s_filename_402032f0);
              uVar6 = FUN_40202224(param_1,auStack_b0);
              FUN_40215e1c(auStack_b0);
            }
            FUN_40215e1c(auStack_a4);
            if (uVar6 == 0) {
              uVar6 = uStack_50;
            }
            else {
              FUN_40216338(auStack_b0,PTR_s_filename_402032f0);
              uVar8 = FUN_402023fc(param_1,auStack_b0);
              FUN_402160d4(auStack_98,uVar8);
              FUN_40215e1c(auStack_b0);
            }
          }
          FUN_40216300(auStack_8c,*(undefined4 *)(PTR_PTR_402032f4 + 0x14));
          FUN_40214fec(auStack_b0,param_2,0xd);
          FUN_4021612c(auStack_68,auStack_b0);
          FUN_40215e1c(auStack_b0);
          FUN_40214fec(auStack_b0,param_2,10);
          FUN_40215e1c(auStack_b0);
          uVar7 = FUN_402226bc(auStack_68);
          if (0xc < uVar7) {
            FUN_40216c00(auStack_a4,auStack_68,0);
            FUN_40216338(auStack_b0,PTR_s_Content_Type_402032f8);
            puStack_34 = (uint *)FUN_40216838(auStack_a4,auStack_b0);
            FUN_40215e1c(auStack_b0);
            FUN_40215e1c(auStack_a4);
            if (puStack_34 != (uint *)0x0) {
              iVar4 = FUN_40216a98(auStack_68,0x3a,0);
              FUN_40201628(auStack_b0,auStack_68,iVar4 + 2);
              FUN_4021612c(auStack_8c,auStack_b0);
              FUN_40215e1c(auStack_b0);
              FUN_40214fec(auStack_b0,param_2,0xd);
              FUN_40215e1c(auStack_b0);
              FUN_40214fec(auStack_b0,param_2,10);
              FUN_40215e1c(auStack_b0);
            }
          }
          puVar1 = PTR_DAT_402032e4;
          if (uVar6 != 0) {
            puStack_44 = puVar2;
            uVar8 = FUN_4021703c(0x834);
            uVar8 = (*(code *)PTR_FUN_40203300)(uVar8,0,0x834);
            iVar4 = *(int *)(param_1 + 0x98);
            *(undefined4 *)(param_1 + 0x98) = uVar8;
            if (iVar4 != 0) {
              FUN_40201260();
            }
            puVar5 = *(undefined4 **)(param_1 + 0x98);
            *puVar5 = 0;
            FUN_402160d4(puVar5 + 4,auStack_74);
            FUN_402160d4(*(int *)(param_1 + 0x98) + 4,auStack_98);
            FUN_402160d4(*(int *)(param_1 + 0x98) + 0x1c,auStack_8c);
            iVar4 = *(int *)(param_1 + 0x98);
            *(undefined4 *)(iVar4 + 0x28) = 0;
            *(undefined4 *)(iVar4 + 0x2c) = 0;
            *(undefined4 *)(iVar4 + 0x30) = uStack_38;
            piVar9 = *(int **)(param_1 + 0x60);
            if (piVar9 != (int *)0x0) {
              iVar4 = (**(code **)(*piVar9 + 0xc))(piVar9,param_1 + 0x48);
              if (iVar4 != 0) {
                (**(code **)(**(int **)(param_1 + 0x60) + 0x14))
                          (*(int **)(param_1 + 0x60),param_1,param_1 + 0x48,
                           *(undefined4 *)(param_1 + 0x98));
              }
            }
            **(undefined4 **)(param_1 + 0x98) = 1;
            iVar3 = FUN_402226bc(puStack_4c);
            iStack_3c = iVar3 + 4;
            iVar4 = -(iVar3 + 0x14U & 0xfffffff0);
            pbStack_48 = puVar2 + iVar4;
            puVar5 = puStack_4c;
            if ((*(byte *)((int)puStack_4c + 0xb) & 0x80) != 0) {
              puVar5 = (undefined4 *)*puStack_4c;
            }
            FUN_40227418((int)puVar2 + iVar4,iVar3 + 5,PTR_s____s_402032fc,puVar5);
            do {
              iVar4 = 0;
LAB_4020379a:
              do {
                puVar10 = (uint *)(**(code **)(*param_2 + 0x18))(param_2);
                if (puVar10 == (uint *)0xffffffff) {
                  while ((iVar3 = (**(code **)(*param_2 + 0x14))(param_2), iVar3 == 0 &&
                         (iVar3 = (**(code **)(*param_2 + 0x54))(param_2), iVar3 != 0))) {
                    FUN_402173a8();
                  }
                  puVar10 = (uint *)(**(code **)(*param_2 + 0x18))(param_2);
                }
                if ((int)puVar10 < 0) {
LAB_4020389f:
                  uStack_50 = FUN_40222780(param_1);
                  FUN_40215e1c(auStack_98);
                  FUN_40215e1c(auStack_8c);
                  FUN_40215e1c(auStack_80);
                  FUN_40215e1c(auStack_74);
                  goto LAB_40203a77;
                }
                if ((uint *)(uint)pbStack_48[iVar4] == (uint *)((uint)puVar10 & 0xff)) {
                  iVar4 = iVar4 + 1;
                  if (iStack_3c == iVar4) {
                    piVar9 = *(int **)(param_1 + 0x60);
                    if (piVar9 != (int *)0x0) {
                      iVar4 = (**(code **)(*piVar9 + 0xc))(piVar9,param_1 + 0x48);
                      if (iVar4 != 0) {
                        (**(code **)(**(int **)(param_1 + 0x60) + 0x14))
                                  (*(int **)(param_1 + 0x60),param_1,param_1 + 0x48,
                                   *(undefined4 *)(param_1 + 0x98));
                      }
                    }
                    puVar5 = *(undefined4 **)(param_1 + 0x98);
                    puVar5[10] = puVar5[10] + puVar5[0xb];
                    *puVar5 = 2;
                    piVar9 = *(int **)(param_1 + 0x60);
                    if (piVar9 != (int *)0x0) {
                      iVar4 = (**(code **)(*piVar9 + 0xc))(piVar9,param_1 + 0x48);
                      if (iVar4 != 0) {
                        (**(code **)(**(int **)(param_1 + 0x60) + 0x14))
                                  (*(int **)(param_1 + 0x60),param_1,param_1 + 0x48,
                                   *(undefined4 *)(param_1 + 0x98));
                      }
                    }
                    iVar4 = (**(code **)(*param_2 + 0x54))(param_2);
                    if (iVar4 == 0) goto LAB_4020389f;
                    FUN_40214fec(auStack_b0,param_2,0xd);
                    FUN_4021612c(auStack_68,auStack_b0);
                    FUN_40215e1c(auStack_b0);
                    FUN_40214fec(auStack_b0,param_2,10);
                    FUN_40215e1c(auStack_b0);
                    iVar4 = FUN_402167d0(auStack_68,PTR_DAT_402032e4);
                    if (iVar4 != 0) goto LAB_40203923;
                    puVar2 = puStack_44;
                    goto LAB_40203908;
                  }
                  goto LAB_4020379a;
                }
                uVar6 = 0;
                puVar11 = (uint *)((uint)puVar10 & 0xff);
                while ((int)uVar6 < iVar4) {
                  puStack_34 = puVar11;
                  puStack_30 = puVar10;
                  uStack_2c = uVar6;
                  FUN_402227c8(param_1,pbStack_48[uVar6]);
                  puVar10 = puStack_30;
                  puVar11 = puStack_34;
                  uVar6 = uStack_2c + 1;
                }
                iVar4 = 1;
              } while ((uint *)(uint)*pbStack_48 == puVar11);
              FUN_402227c8(param_1,(uint)puVar10 & 0xff);
            } while( true );
          }
          while( true ) {
            FUN_40214fec(auStack_b0,param_2,0xd);
            FUN_4021612c(auStack_68,auStack_b0);
            FUN_40215e1c(auStack_b0);
            FUN_40214fec(auStack_b0,param_2,10);
            FUN_40215e1c(auStack_b0);
            FUN_402166bc(auStack_b0,puVar1,puStack_4c);
            puStack_34 = (uint *)FUN_40216988(auStack_68,auStack_b0);
            FUN_40215e1c(auStack_b0);
            if (puStack_34 != (uint *)0x0) break;
            iVar4 = FUN_402226bc(auStack_80);
            if (iVar4 != 0) {
              FUN_4021649c(auStack_80,10);
            }
            FUN_402163d0(auStack_80,auStack_68);
          }
          puStack_30 = (uint *)(*(int *)(param_1 + 0x9c) * 0x18 + *(int *)(param_1 + 0xa0));
          *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + 1;
          FUN_402160d4(puStack_30,auStack_74);
          FUN_402160d4(puStack_30 + 3,auStack_80);
          FUN_402166bc(auStack_a4,puVar1,puStack_4c);
          FUN_4021646c(auStack_a4,puVar1);
          FUN_402160bc(auStack_b0,auStack_a4);
          iVar4 = FUN_4021678c(auStack_68,auStack_b0);
          FUN_40215e1c(auStack_b0);
          FUN_40215e1c(auStack_a4);
          if (iVar4 != 0) goto LAB_40203923;
        }
      }
LAB_40203908:
      FUN_40215e1c(auStack_98);
      FUN_40215e1c(auStack_8c);
      FUN_40215e1c(auStack_80);
      FUN_40215e1c(auStack_74);
    } while( true );
  }
LAB_40203a77:
  FUN_40215e1c(auStack_68);
  return uStack_50;
LAB_40203923:
  FUN_40215e1c(auStack_98);
  FUN_40215e1c(auStack_8c);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  uVar6 = 0x20 - *(int *)(param_1 + 0x9c);
  if ((int)*(uint *)(param_1 + 0x8c) < (int)uVar6) {
    uVar6 = *(uint *)(param_1 + 0x8c);
  }
  for (iVar4 = 0; iVar3 = *(int *)(param_1 + 0x90), iVar4 < (int)uVar6; iVar4 = iVar4 + 1) {
    iVar12 = *(int *)(param_1 + 0x9c) * 0x18 + *(int *)(param_1 + 0xa0);
    *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + 1;
    puStack_30 = (uint *)(iVar4 * 0x18);
    uStack_2c = uVar6;
    FUN_402160d4(iVar12,iVar4 * 0x18 + iVar3);
    FUN_402160d4(iVar12 + 0xc,(int)puStack_30 + *(int *)(param_1 + 0x90) + 0xc);
    uVar6 = uStack_2c;
  }
  if (iVar3 != 0) {
    iVar3 = *(int *)(iVar3 + -4) * 0x18 + iVar3;
    while (*(int *)(param_1 + 0x90) != iVar3) {
      iVar3 = iVar3 + -0x18;
      FUN_4020305c(iVar3);
    }
    FUN_4022e938((int *)(iVar3 + -4),*(int *)(iVar3 + -4) * 0x18 + 4);
  }
  uVar6 = *(uint *)(param_1 + 0x9c);
  iVar4 = -1;
  if (uVar6 <= DAT_40203218) {
    iVar4 = uVar6 * 0x18 + 4;
  }
  puVar11 = (uint *)FUN_40217074(iVar4);
  *puVar11 = uVar6;
  puVar10 = puVar11 + 1;
  while (uVar6 = uVar6 - 1, -1 < (int)uVar6) {
    puStack_34 = puVar10;
    FUN_40222774(puVar10);
    puVar10 = puStack_34 + 6;
  }
  *(uint **)(param_1 + 0x90) = puVar11 + 1;
  for (iVar4 = 0; iVar3 = *(int *)(param_1 + 0xa0), iVar4 < *(int *)(param_1 + 0x9c);
      iVar4 = iVar4 + 1) {
    iVar12 = iVar4 * 0x18 + *(int *)(param_1 + 0x90);
    puStack_30 = (uint *)(iVar4 * 0x18);
    FUN_402160d4(iVar12,iVar4 * 0x18 + iVar3);
    FUN_402160d4(iVar12 + 0xc,(int)puStack_30 + *(int *)(param_1 + 0xa0) + 0xc);
  }
  *(int *)(param_1 + 0x8c) = iVar4;
  if (iVar3 != 0) {
    iVar3 = *(int *)(iVar3 + -4) * 0x18 + iVar3;
    while (*(int *)(param_1 + 0xa0) != iVar3) {
      iVar3 = iVar3 + -0x18;
      FUN_4020305c(iVar3);
    }
    FUN_4022e938((int *)(iVar3 + -4),*(int *)(iVar3 + -4) * 0x18 + 4);
    *(undefined4 *)(param_1 + 0xa0) = 0;
    *(undefined4 *)(param_1 + 0x9c) = 0;
  }
  goto LAB_40203a77;
}



/* ==== 40203ae0  FUN_40203ae0  size=1714 ==== */

int FUN_40203ae0(int param_1,int ****param_2)

{
  undefined *puVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 ****ppppuVar5;
  int iVar6;
  undefined4 ****ppppuVar7;
  int ****ppppiVar8;
  int *piVar9;
  uint uVar10;
  undefined *local_d0;
  int iStack_cc;
  undefined4 uStack_c8;
  int iStack_c0;
  int ****ppppiStack_bc;
  undefined4 uStack_b8;
  int ****local_b4 [2];
  uint uStack_ac;
  undefined4 ****local_a8 [2];
  uint uStack_a0;
  undefined4 ****local_9c [2];
  uint uStack_94;
  undefined4 ***apppuStack_90 [2];
  undefined4 uStack_88;
  undefined4 auStack_84 [2];
  undefined4 uStack_7c;
  undefined4 auStack_78 [2];
  undefined4 uStack_70;
  undefined4 ****local_6c [2];
  byte bStack_61;
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [24];
  int iStack_30;
  int *piStack_2c;
  int *piStack_28;
  int iStack_24;
  
  FUN_40214fec(auStack_48,param_2,0xd);
  FUN_40214fec(&local_d0,param_2,10);
  FUN_40215e1c(&local_d0);
  for (iVar6 = 0; iVar6 < *(int *)(param_1 + 0xa4); iVar6 = iVar6 + 1) {
    iVar3 = iVar6 * 0x18 + *(int *)(param_1 + 0xa8);
    if ((*(byte *)(iVar3 + 0x17) & 0x80) == 0) {
      *(undefined1 *)(iVar3 + 0x17) = 0;
    }
    else {
      *(undefined2 *)(iVar3 + 0x12) = 0;
    }
  }
  iStack_24 = FUN_40216a98(auStack_48,0x20,0);
  piStack_28 = (int *)(iStack_24 + 1);
  iVar6 = FUN_40216a98(auStack_48,0x20,piStack_28);
  piVar9 = (int *)2;
  if (piStack_28 == (int *)0x0 || iVar6 == -1) goto LAB_40204180;
  FUN_40216c00(auStack_54,auStack_48,0,iStack_24);
  FUN_40216c00(auStack_60,auStack_48,piStack_28,iVar6);
  FUN_40201628(local_6c,auStack_48,iVar6 + 8);
  ppppuVar5 = local_6c;
  if ((bStack_61 & 0x80) != 0) {
    ppppuVar5 = local_6c[0];
  }
  uVar2 = FUN_40225aa4(ppppuVar5);
  *(undefined1 *)(param_1 + 0x54) = uVar2;
  auStack_78[0] = 0;
  uStack_70 = 0;
  iVar6 = FUN_40216a98(auStack_60,0x3f,0);
  if (iVar6 != -1) {
    iStack_24 = iVar6;
    FUN_40201628(&local_d0,auStack_60,iVar6 + 1);
    FUN_4021612c(auStack_78,&local_d0);
    FUN_40215e1c(&local_d0);
    FUN_40216c00(&local_d0,auStack_60,0,iStack_24);
    FUN_4021612c(auStack_60,&local_d0);
    FUN_40215e1c(&local_d0);
  }
  FUN_402160d4(param_1 + 0x48,auStack_60);
  *(undefined1 *)(param_1 + 200) = 0;
  if (*(int *)(param_1 + 0xf8) == 0) {
LAB_40203c21:
    FUN_40216338(&local_d0,PTR_DAT_40203a94);
    piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
    FUN_40215e1c(&local_d0);
    iVar6 = 2;
    if (piStack_28 == (int *)0x0) {
      FUN_40216338(&local_d0,PTR_DAT_40203a9c);
      piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
      FUN_40215e1c(&local_d0);
      iVar6 = 3;
      if (piStack_28 == (int *)0x0) {
        FUN_40216338(&local_d0,PTR_s_DELETE_40203aa0);
        piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
        FUN_40215e1c(&local_d0);
        iVar6 = 6;
        if (piStack_28 == (int *)0x0) {
          FUN_40216338(&local_d0,PTR_s_OPTIONS_40203aa4);
          piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
          FUN_40215e1c(&local_d0);
          iVar6 = 7;
          if (piStack_28 == (int *)0x0) {
            FUN_40216338(&local_d0,PTR_DAT_40203aa8);
            piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
            FUN_40215e1c(&local_d0);
            iVar6 = 4;
            if (piStack_28 == (int *)0x0) {
              FUN_40216338(&local_d0,PTR_s_PATCH_40203aac);
              piStack_28 = (int *)FUN_4021678c(auStack_54,&local_d0);
              FUN_40215e1c(&local_d0);
              iVar6 = 1;
              if (piStack_28 != (int *)0x0) {
                iVar6 = 5;
              }
            }
          }
        }
      }
    }
    piVar9 = *(int **)(param_1 + 100);
    *(int *)(param_1 + 0x44) = iVar6;
    *(bool *)(param_1 + 0xca) = *(char *)(param_1 + 0x54) != '\0';
    while ((piVar9 != (int *)0x0 &&
           (piStack_28 = piVar9, iStack_24 = iVar6,
           iVar3 = (**(code **)(*piVar9 + 8))(piVar9,*(undefined4 *)(param_1 + 0x44),param_1 + 0x48)
           , iVar6 = iStack_24, piVar9 = piStack_28, iVar3 == 0))) {
      piVar9 = (int *)piStack_28[1];
    }
    uVar10 = 0;
    *(int **)(param_1 + 0x60) = piVar9;
    auStack_84[0] = 0;
    uStack_7c = 0;
    if (iVar6 - 3U < 4) {
      apppuStack_90[0] = (undefined4 ***)0x0;
      uStack_88 = 0;
      local_9c[0] = (undefined4 ****)0x0;
      uStack_94 = 0;
      local_a8[0] = (undefined4 ****)0x0;
      uStack_a0 = 0;
      piStack_2c = (int *)0x0;
      do {
        iStack_30 = 0;
LAB_40203d82:
        FUN_40214fec(&local_d0,param_2,0xd);
        FUN_4021612c(auStack_48,&local_d0);
        FUN_40215e1c(&local_d0);
        FUN_40214fec(&local_d0,param_2,10);
        FUN_40215e1c(&local_d0);
        iVar6 = FUN_402226bc(auStack_48);
        if ((iVar6 == 0) || (iVar6 = FUN_40216a98(auStack_48,0x3a,0), iVar6 == -1)) {
          local_b4[0] = (int ****)0x0;
          uStack_ac = 0;
          if (iStack_30 == 0) {
            iStack_cc = iStack_30;
            uStack_c8 = 1000;
            iStack_c0 = iStack_30;
            local_d0 = PTR_PTR_40203acc;
            uStack_b8 = 0xffffffff;
            ppppiStack_bc = (int ****)local_b4;
            uVar4 = FUN_40215444(param_2,&local_d0,uVar10,0xffffffff,5000);
            if ((uVar10 == uVar4) && (uVar4 = FUN_402226bc(local_b4), uVar10 <= uVar4))
            goto LAB_40203f5c;
LAB_4020401c:
            FUN_40215e1c(local_b4);
            FUN_40215e1c(local_a8);
            FUN_40215e1c(local_9c);
            FUN_40215e1c(apppuStack_90);
            piStack_28 = (int *)0x2;
            goto LAB_40204156;
          }
LAB_40203f5c:
          if (piStack_2c != (int *)0x0) {
            iVar6 = FUN_402226bc(auStack_78);
            if (iVar6 != 0) {
              FUN_4021649c(auStack_78,0x26);
            }
            FUN_402163d0(auStack_78,local_b4);
          }
          FUN_40203224(param_1,auStack_78);
          puVar1 = PTR_s_plain_40203ad0;
          if (iStack_30 == 0) {
            if (uVar10 != 0) {
              iVar6 = *(int *)(param_1 + 0x8c) * 0x18 + *(int *)(param_1 + 0x90);
              *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
              FUN_40216300(iVar6,puVar1);
              FUN_402160d4(iVar6 + 0xc,local_b4);
              *(undefined4 *)(param_1 + 0x94) = 1;
            }
          }
          else {
            iVar6 = FUN_40203304(param_1,param_2,apppuStack_90,uVar10);
            if (iVar6 == 0) goto LAB_4020401c;
          }
          FUN_40215e1c(local_b4);
          FUN_40215e1c(local_a8);
          FUN_40215e1c(local_9c);
          ppppuVar5 = apppuStack_90;
          goto LAB_40204146;
        }
        piStack_28 = (int *)iVar6;
        FUN_40216c00(&local_d0,auStack_48,0,iVar6);
        FUN_4021612c(local_9c,&local_d0);
        FUN_40215e1c(&local_d0);
        FUN_40201628(&local_d0,auStack_48,(int)piStack_28 + 1);
        FUN_4021612c(local_a8,&local_d0);
        FUN_40215e1c(&local_d0);
        FUN_40216f38(local_a8);
        ppppuVar5 = local_9c;
        if ((uStack_94 & 0x80000000) != 0) {
          ppppuVar5 = local_9c[0];
        }
        ppppuVar7 = local_a8;
        if ((uStack_a0 & 0x80000000) != 0) {
          ppppuVar7 = local_a8[0];
        }
        FUN_40201294(param_1,ppppuVar5,ppppuVar7);
        FUN_40216338(&local_d0,PTR_s_Content_Type_402032f8);
        piStack_28 = (int *)FUN_40216838(local_9c,&local_d0);
        FUN_40215e1c(&local_d0);
        if (piStack_28 == (int *)0x0) {
          FUN_40216338(&local_d0,PTR_s_Content_Length_40203abc);
          piStack_28 = (int *)FUN_40216838(local_9c,&local_d0);
          FUN_40215e1c(&local_d0);
          if (piStack_28 == (int *)0x0) {
            FUN_40216338(&local_d0,PTR_DAT_40203ac0);
            piStack_28 = (int *)FUN_40216838(local_9c,&local_d0);
            FUN_40215e1c(&local_d0);
            if (piStack_28 == (int *)0x0) {
              FUN_40216338(&local_d0,PTR_s_Connection_40203ac4);
              piStack_28 = (int *)FUN_40216838(local_9c,&local_d0);
              FUN_40215e1c(&local_d0);
              if (piStack_28 != (int *)0x0) {
                FUN_40216338(&local_d0,PTR_s_keep_alive_40203ac8);
                uVar2 = FUN_40216838(local_a8,&local_d0);
                *(undefined1 *)(param_1 + 0xca) = uVar2;
                FUN_40215e1c(&local_d0);
              }
            }
            else {
              FUN_402160d4(param_1 + 0xbc,local_a8);
            }
          }
          else {
            uVar10 = FUN_40216fe4(local_a8);
          }
          goto LAB_40203d82;
        }
        iVar6 = FUN_402015d0(local_a8,*(undefined4 *)(PTR_PTR_402032f4 + 0x14));
        if (iVar6 == 0) {
          iStack_24 = iVar6;
          piVar9 = (int *)FUN_402015d0(local_a8,PTR_s_application_x_www_form_urlencode_40203ab0);
          if (piVar9 == (int *)0x0) {
            piStack_28 = piVar9;
            iVar6 = FUN_402015d0(local_a8,PTR_s_multipart__40203ab4);
            if (iVar6 == 0) goto LAB_40203d82;
            iStack_24 = iVar6;
            iVar6 = FUN_40216a98(local_a8,0x3d,piStack_28);
            FUN_40201628(&local_d0,local_a8,iVar6 + 1);
            FUN_4021612c(apppuStack_90,&local_d0);
            FUN_40215e1c(&local_d0);
            FUN_40201658(apppuStack_90,PTR_s___3ffe8df0_0x11_40203ab8,PTR_DAT_40201938);
          }
          else {
            piStack_2c = piVar9;
          }
          iStack_30 = iStack_24;
          goto LAB_40203d82;
        }
      } while( true );
    }
    local_a8[0] = (undefined4 ****)0x0;
    uStack_a0 = 0;
    local_b4[0] = (int ****)0x0;
    uStack_ac = 0;
    while( true ) {
      FUN_40214fec(&local_d0,param_2,0xd);
      FUN_4021612c(auStack_48,&local_d0);
      FUN_40215e1c(&local_d0);
      FUN_40214fec(&local_d0,param_2,10);
      FUN_40215e1c(&local_d0);
      iVar6 = FUN_402226bc(auStack_48);
      if ((iVar6 == 0) || (iVar6 = FUN_40216a98(auStack_48,0x3a,0), iVar6 == -1)) break;
      FUN_40216c00(&local_d0,auStack_48,0,iVar6);
      FUN_4021612c(local_a8,&local_d0);
      FUN_40215e1c(&local_d0);
      FUN_40201628(&local_d0,auStack_48,iVar6 + 2);
      FUN_4021612c(local_b4,&local_d0);
      FUN_40215e1c(&local_d0);
      ppppuVar5 = local_a8;
      if ((uStack_a0 & 0x80000000) != 0) {
        ppppuVar5 = local_a8[0];
      }
      ppppiVar8 = (int ****)local_b4;
      if ((uStack_ac & 0x80000000) != 0) {
        ppppiVar8 = local_b4[0];
      }
      FUN_40201294(param_1,ppppuVar5,ppppiVar8);
      FUN_40216338(&local_d0,PTR_DAT_40203ad4);
      iVar6 = FUN_40216838(local_a8,&local_d0);
      FUN_40215e1c(&local_d0);
      if (iVar6 == 0) {
        FUN_40216338(&local_d0,PTR_s_Connection_40203ad8);
        iVar6 = FUN_40216838(local_a8,&local_d0);
        FUN_40215e1c(&local_d0);
        if (iVar6 != 0) {
          FUN_40216338(&local_d0,PTR_s_keep_alive_40203adc);
          uVar2 = FUN_40216838(local_b4,&local_d0);
          *(undefined1 *)(param_1 + 0xca) = uVar2;
          FUN_40215e1c(&local_d0);
        }
      }
      else {
        FUN_402160d4(param_1 + 0xbc,local_b4);
      }
    }
    FUN_40203224(param_1,auStack_78);
    FUN_40215e1c(local_b4);
    ppppuVar5 = local_a8;
LAB_40204146:
    FUN_40215e1c(ppppuVar5);
    (*(code *)(*param_2)[3])(param_2);
    piStack_28 = (int *)0x0;
LAB_40204156:
    FUN_40215e1c(auStack_84);
    piVar9 = piStack_28;
  }
  else {
    local_d0 = PTR_FUN_40203a98;
    local_b4[0] = param_2;
    piVar9 = (int *)(**(code **)(param_1 + 0xfc))
                              (param_1 + 0xf0,auStack_54,auStack_60,local_b4,&local_d0);
    if (piVar9 == (int *)0x0) goto LAB_40203c21;
  }
  piStack_28 = piVar9;
  FUN_40215e1c(auStack_78);
  FUN_40215e1c(local_6c);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  piVar9 = piStack_28;
LAB_40204180:
  piStack_28 = piVar9;
  FUN_40215e1c(auStack_48);
  return (int)piStack_28;
}



/* ==== 402041b0  FUN_402041b0  size=109 ==== */

void FUN_402041b0(int param_1,int *param_2,int param_3)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x44) != 2) {
    if (param_3 < 1) {
      iVar1 = (**(code **)(*param_2 + 0x44))(param_2);
      param_3 = 0;
      if (-1 < iVar1) {
        param_3 = iVar1;
      }
    }
    iVar1 = param_1 + 0x24;
    if (*(char *)(param_1 + 200) != '\0') {
      FUN_40214990(iVar1,PTR_s__zx_402041a8,param_3);
    }
    FUN_40215444(param_2,iVar1,param_3,0xffffffff);
    if ((*(char *)(param_1 + 200) != '\0') && (FUN_40214a58(iVar1,PTR_DAT_402041ac), param_3 == 0))
    {
      *(undefined1 *)(param_1 + 200) = 0;
    }
  }
  return;
}



/* ==== 40204220  FUN_40204220  size=47 ==== */

bool FUN_40204220(undefined4 *param_1,char param_2)

{
  bool bVar1;
  
  FUN_40222834();
  bVar1 = *(char *)*param_1 == param_2;
  if (bVar1) {
    *param_1 = (char *)*param_1 + 1;
  }
  return bVar1;
}



/* ==== 40204254  FUN_40204254  size=90 ==== */

int FUN_40204254(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 4);
  do {
    if (piVar3 == (int *)0x0) {
      return 0;
    }
    if ((*(byte *)((int)param_2 + 0xb) & 0x80) == 0) {
      puVar1 = param_2;
    }
    else {
      puVar1 = (undefined4 *)*param_2;
    }
    if ((puVar1 == (undefined4 *)0x0) || ((undefined4 *)piVar3[1] == (undefined4 *)0x0)) {
      if ((undefined4 *)piVar3[1] == puVar1) {
        return (int)piVar3;
      }
    }
    else {
      iVar2 = (*(code *)PTR_FUN_40204250)();
      if (iVar2 == 0) {
        return (int)piVar3;
      }
    }
    piVar3 = (int *)*piVar3;
  } while( true );
}



/* ==== 402042b0  FUN_402042b0  size=51 ==== */

void FUN_402042b0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)FUN_402226d8(0x10,*param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[2] = 0;
  }
  puVar3 = (undefined4 *)param_1[1];
  if ((undefined4 *)param_1[1] == (undefined4 *)0x0) {
    param_1[1] = puVar1;
  }
  else {
    do {
      puVar2 = puVar3;
      puVar3 = (undefined4 *)*puVar2;
    } while (puVar3 != (undefined4 *)0x0);
    *puVar2 = puVar1;
  }
  return;
}



/* ==== 40204398  FUN_40204398  size=417 ==== */

undefined4 FUN_40204398(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_402042e4;
  if (param_2 < 0x1a2) {
    if (param_2 < 400) {
      if (param_2 < 0xcf) {
        if (param_2 < 200) {
          puVar1 = PTR_s_Continue_402042e8;
          if ((param_2 != 100) && (puVar1 = PTR_DAT_402042e4, param_2 == 0x65)) {
            puVar1 = PTR_s_Switching_Protocols_4020436c;
          }
        }
        else {
          puVar1 = PTR_DAT_40204384;
          switch(param_2) {
          case 0xc9:
            puVar1 = PTR_s_Created_402042f0;
            break;
          case 0xca:
            puVar1 = PTR_s_Accepted_402042f4;
            break;
          case 0xcb:
            puVar1 = PTR_s_Non_Authoritative_Information_402042f8;
            break;
          case 0xcc:
            puVar1 = PTR_s_No_Content_402042fc;
            break;
          case 0xcd:
            puVar1 = PTR_s_Reset_Content_40204300;
            break;
          case 0xce:
            puVar1 = PTR_s_Partial_Content_40204304;
          }
        }
      }
      else {
        switch(param_2) {
        case 300:
          puVar1 = PTR_s_Multiple_Choices_402042ec;
          break;
        case 0x12d:
          puVar1 = PTR_s_Moved_Permanently_4020430c;
          break;
        case 0x12e:
          puVar1 = PTR_s_Found_40204310;
          break;
        case 0x12f:
          puVar1 = PTR_s_See_Other_40204314;
          break;
        case 0x130:
          puVar1 = PTR_s_Not_Modified_40204318;
          break;
        case 0x131:
          puVar1 = PTR_s_Use_Proxy_4020431c;
          break;
        case 0x132:
          break;
        case 0x133:
          puVar1 = PTR_s_Temporary_Redirect_40204320;
        }
      }
    }
    else {
      puVar1 = PTR_s_Bad_Request_40204308;
      switch(param_2) {
      case 0x191:
        puVar1 = PTR_s_Unauthorized_40204328;
        break;
      case 0x192:
        puVar1 = PTR_s_Payment_Required_4020432c;
        break;
      case 0x193:
        puVar1 = PTR_s_Forbidden_40204330;
        break;
      case 0x194:
        puVar1 = PTR_s_Not_Found_40204334;
        break;
      case 0x195:
        puVar1 = PTR_s_Method_Not_Allowed_40204338;
        break;
      case 0x196:
        puVar1 = PTR_s_Not_Acceptable_4020433c;
        break;
      case 0x197:
        puVar1 = PTR_s_Proxy_Authentication_Required_40204340;
        break;
      case 0x198:
        puVar1 = PTR_s_Request_Timeout_40204344;
        break;
      case 0x199:
        puVar1 = PTR_s_Conflict_40204348;
        break;
      case 0x19a:
        puVar1 = PTR_DAT_4020434c;
        break;
      case 0x19b:
        puVar1 = PTR_s_Length_Required_40204350;
        break;
      case 0x19c:
        puVar1 = PTR_s_Precondition_Failed_40204354;
        break;
      case 0x19d:
        puVar1 = PTR_s_Request_Entity_Too_Large_40204358;
        break;
      case 0x19e:
        puVar1 = PTR_s_URI_Too_Long_4020435c;
        break;
      case 0x19f:
        puVar1 = PTR_s_Unsupported_Media_Type_40204360;
        break;
      case 0x1a0:
        puVar1 = PTR_s_Range_not_satisfiable_40204364;
        break;
      case 0x1a1:
        puVar1 = PTR_s_Expectation_Failed_40204368;
      }
    }
  }
  else {
    switch(param_2) {
    case 500:
      puVar1 = PTR_s_Internal_Server_Error_40204324;
      break;
    case 0x1f5:
      puVar1 = PTR_s_Not_Implemented_40204370;
      break;
    case 0x1f6:
      puVar1 = PTR_s_Bad_Gateway_40204374;
      break;
    case 0x1f7:
      puVar1 = PTR_s_Service_Unavailable_40204378;
      break;
    case 0x1f8:
      puVar1 = PTR_s_Gateway_Timeout_4020437c;
      break;
    case 0x1f9:
      puVar1 = PTR_s_HTTP_Version_not_supported_40204380;
    }
  }
  FUN_40216338(param_1,puVar1);
  return param_1;
}



/* ==== 40204610  FUN_40204610  size=561 ==== */

void FUN_40204610(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  undefined *puVar1;
  int iVar2;
  undefined *puVar3;
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [12];
  int iStack_30;
  
  iStack_30 = param_4;
  FUN_40216338(auStack_3c,PTR_s_HTTP_1__402045e0);
  FUN_402162d0(auStack_48,*(undefined1 *)(param_1 + 0x54),10);
  FUN_40216644(auStack_54,auStack_3c,auStack_48);
  FUN_4021649c(auStack_54,0x20);
  FUN_402160bc(auStack_60,auStack_54);
  FUN_4021612c(param_2,auStack_60);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  FUN_40215e1c(auStack_48);
  FUN_40215e1c(auStack_3c);
  FUN_40216290(auStack_60,param_3,10);
  FUN_402163d0(param_2,auStack_60);
  FUN_40215e1c(auStack_60);
  FUN_4021649c(param_2,0x20);
  FUN_40204398(auStack_60,param_3);
  FUN_402163d0(param_2,auStack_60);
  FUN_40215e1c(auStack_60);
  puVar1 = PTR_s__3ffe978f_0x16_40202de4;
  FUN_4021646c(param_2,PTR_s__3ffe978f_0x16_40202de4);
  if (iStack_30 == 0) {
    iStack_30 = *(int *)(PTR_PTR_402032f4 + 4);
  }
  FUN_40216338(auStack_54,PTR_s_Content_Type_402045e4);
  FUN_40216338(auStack_60,iStack_30);
  FUN_40202de8(param_1,auStack_54,auStack_60,1);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  puVar3 = PTR_s_Accept_Ranges_402045ec;
  if (*(int *)(param_1 + 0xac) == -2) {
    FUN_40216338(auStack_54,PTR_s_Content_Length_402045e8);
LAB_4020470b:
    FUN_40216260(auStack_60,param_5,10);
  }
  else {
    if (*(int *)(param_1 + 0xac) != -1) {
      FUN_40216338(auStack_54,PTR_s_Content_Length_402045e8);
      param_5 = *(undefined4 *)(param_1 + 0xac);
      goto LAB_4020470b;
    }
    if (*(char *)(param_1 + 0x54) == '\0') goto LAB_4020476a;
    *(undefined1 *)(param_1 + 200) = 1;
    FUN_40216338(auStack_54,puVar3);
    FUN_40216338(auStack_60,PTR_DAT_402045f0);
    FUN_40202de8(param_1,auStack_54,auStack_60,0);
    FUN_40215e1c(auStack_60);
    FUN_40215e1c(auStack_54);
    FUN_40216338(auStack_54,PTR_s_Transfer_Encoding_402045f4);
    FUN_40216338(auStack_60,PTR_s_chunked_402045f8);
  }
  FUN_40202de8(param_1,auStack_54,auStack_60,0);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
LAB_4020476a:
  if (*(char *)(param_1 + 0xc9) != '\0') {
    FUN_40216338(auStack_54,PTR_s_Access_Control_Allow_Origin_402045fc);
    FUN_40216000(auStack_60,PTR_DAT_40204600);
    FUN_40202de8(param_1,auStack_54,auStack_60,0);
    FUN_40215e1c(auStack_60);
    FUN_40215e1c(auStack_54);
  }
  if ((*(char *)(param_1 + 0xca) != '\0') && (iVar2 = FUN_40222a70(param_1), iVar2 != 0)) {
    *(undefined1 *)(param_1 + 0xca) = 0;
  }
  FUN_40216338(auStack_54,PTR_s_Connection_40204604);
  puVar3 = PTR_s_keep_alive_402045d8;
  if (*(char *)(param_1 + 0xca) == '\0') {
    puVar3 = PTR_s_close_402045dc;
  }
  FUN_40216338(auStack_60,puVar3);
  FUN_40202de8(param_1,auStack_54,auStack_60,0);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  if (*(char *)(param_1 + 0xca) != '\0') {
    FUN_40216338(auStack_48,PTR_s_Keep_Alive_40204608);
    FUN_40216338(auStack_54,PTR_s_timeout__4020460c);
    FUN_402164b8(auStack_54,2000);
    FUN_402160bc(auStack_60,auStack_54);
    FUN_40202de8(param_1,auStack_48,auStack_60,0);
    FUN_40215e1c(auStack_60);
    FUN_40215e1c(auStack_54);
    FUN_40215e1c(auStack_48);
  }
  FUN_402163d0(param_2,param_1 + 0xb0);
  FUN_4021646c(param_2,puVar1);
  FUN_4021614c(param_1 + 0xb0,PTR_DAT_40201938);
  return;
}



/* ==== 40204848  FUN_40204848  size=165 ==== */

void FUN_40204848(int param_1,undefined4 param_2,undefined4 param_3,int *param_4,int param_5)

{
  int iVar1;
  undefined *local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_50;
  undefined4 ***pppuStack_4c;
  undefined4 uStack_48;
  undefined1 uStack_44;
  undefined4 uStack_40;
  undefined4 ***local_3c [2];
  uint uStack_34;
  undefined4 uStack_30;
  
  local_3c[0] = (undefined4 ***)0x0;
  uStack_34 = 0;
  if (param_5 == 0) {
    uStack_30 = param_3;
    iVar1 = (**(code **)(*param_4 + 0x44))(param_4);
    param_3 = uStack_30;
    if (-1 < iVar1) {
      param_5 = iVar1;
    }
  }
  FUN_40204610(param_1,local_3c,param_2,param_3,param_5);
  uStack_5c = 0;
  uStack_50 = 0;
  uStack_58 = 1000;
  local_60 = PTR_PTR_40204844;
  pppuStack_4c = local_3c;
  if ((uStack_34 & 0x80000000) != 0) {
    pppuStack_4c = local_3c[0];
  }
  uStack_48 = FUN_402226bc(local_3c);
  uStack_44 = 1;
  uStack_40 = 0;
  FUN_40215444(&local_60,param_1 + 0x24,0xffffffff,0xffffffff);
  if (param_5 != 0) {
    FUN_402041b0(param_1,param_4,param_5);
  }
  FUN_40215e1c(local_3c);
  return;
}



/* ==== 402048f8  FUN_402048f8  size=124 ==== */

void FUN_402048f8(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined4 ****ppppuVar1;
  undefined *local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_40;
  uint uStack_3c;
  undefined4 uStack_38;
  undefined1 uStack_34;
  undefined4 uStack_30;
  undefined4 ****local_2c [2];
  byte bStack_21;
  
  uStack_38 = FUN_4022908c(param_4,DAT_402048f0);
  uStack_48 = 1000;
  local_50 = PTR_PTR_40204844;
  uStack_4c = 0;
  uStack_40 = 0;
  uStack_34 = param_4 <= DAT_402048f4;
  uStack_30 = 0;
  uStack_3c = param_4;
  FUN_40216000(local_2c,param_3);
  ppppuVar1 = local_2c;
  if ((bStack_21 & 0x80) != 0) {
    ppppuVar1 = local_2c[0];
  }
  FUN_40204848(param_1,param_2,ppppuVar1,&local_50,0);
  FUN_40215e1c(local_2c);
  return;
}



/* ==== 40204988  FUN_40204988  size=97 ==== */

void FUN_40204988(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [28];
  
  FUN_40216000(auStack_30,DAT_40204974);
  puVar1 = PTR_DAT_40201fcc;
  uVar2 = FUN_402023fc(PTR_DAT_40201fcc,auStack_30);
  FUN_40216114(auStack_24,uVar2);
  FUN_40215e1c(auStack_30);
  iVar3 = FUN_402167d0(auStack_24,PTR_DAT_40204978);
  if (iVar3 == 0) {
    FUN_402048f8(puVar1,200,PTR_s_text___plain_40204980,PTR_s_No_Reset_40204984);
  }
  else {
    FUN_402048f8(puVar1,200,PTR_s_text___plain_40204980,PTR_s_Reset_OK_4020497c);
    FUN_40212db8();
  }
  FUN_40215e1c(auStack_24);
  return;
}



/* ==== 402049ec  FUN_402049ec  size=37 ==== */

void FUN_402049ec(void)

{
  (*(code *)PTR_FUN_402018a0)(0xd,0);
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 40204a14  FUN_40204a14  size=37 ==== */

void FUN_40204a14(void)

{
  (*(code *)PTR_FUN_402018a0)(0xd,1);
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 40204a3c  FUN_40204a3c  size=49 ==== */

void FUN_40204a3c(void)

{
  (*(code *)PTR_FUN_402018a0)(0xc,0);
  (*(code *)PTR_FUN_402018a0)(0x10,0);
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 40204a74  FUN_40204a74  size=57 ==== */

void FUN_40204a74(void)

{
  (*(code *)PTR_FUN_402018a0)(0xc,1);
  (*(code *)PTR_FUN_402018a0)(0x10,1);
  *PTR_DAT_40204a70 = 0;
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 40204adc  FUN_40204adc  size=225 ==== */

void FUN_40204adc(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 extraout_a4;
  undefined *puVar6;
  undefined1 auStack_70 [44];
  int aiStack_44 [2];
  int iStack_3c;
  undefined1 auStack_38 [36];
  
  puVar2 = PTR_s_text_plain_402022fc;
  puVar1 = PTR_DAT_40201fcc;
  if (*(int *)(PTR_DAT_40201fcc + 0x8c) == 0) {
    FUN_402048f8(PTR_DAT_40201fcc,500,PTR_s_text_plain_402022fc,PTR_s_BAD_ARGS_40204acc);
    return;
  }
  puVar5 = PTR_DAT_40201358;
  if (0 < *(int *)(PTR_DAT_40201fcc + 0x8c) + *(int *)(PTR_DAT_40201fcc + 0x94)) {
    puVar5 = (undefined *)(*(int *)(PTR_DAT_40201fcc + 0x90) + 0xc);
  }
  FUN_40216114(auStack_38,puVar5);
  iVar3 = FUN_402167d0(auStack_38,PTR_s___3ffe96af_0xe_40201cc8);
  puVar5 = PTR_DAT_40201cd0;
  puVar6 = PTR_s_BAD_PATH_40204ad0;
  if (iVar3 == 0) {
    iVar3 = FUN_40213738(PTR_DAT_40201cd0,auStack_38,extraout_a4,PTR_s_BAD_PATH_40204ad0);
    if (iVar3 == 0) {
      FUN_402138b4(auStack_70,puVar5,auStack_38,PTR_DAT_40201ccc);
      iVar4 = FUN_40223178(auStack_70);
      if (iVar4 == 0) {
        FUN_402048f8(puVar1,500,puVar2,PTR_s_CREATE_FAILED_40204ad8);
      }
      else {
        FUN_40213968(auStack_70);
        FUN_402048f8(puVar1,200,puVar2,PTR_DAT_40201938);
        aiStack_44[0] = iVar3;
        iStack_3c = iVar3;
        FUN_4021612c(auStack_38,aiStack_44);
        FUN_40215e1c(aiStack_44);
      }
      FUN_40201ca0(auStack_70);
      goto LAB_40204ba3;
    }
    puVar6 = PTR_s_FILE_EXISTS_40204ad4;
  }
  FUN_402048f8(puVar1,500,puVar2,puVar6);
LAB_40204ba3:
  FUN_40215e1c(auStack_38);
  return;
}



/* ==== 40204bc4  FUN_40204bc4  size=176 ==== */

void FUN_40204bc4(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  int local_40 [2];
  int iStack_38;
  undefined1 auStack_34 [32];
  
  puVar2 = PTR_s_text_plain_402022fc;
  puVar1 = PTR_DAT_40201fcc;
  if (*(int *)(PTR_DAT_40201fcc + 0x8c) == 0) {
    FUN_402048f8(PTR_DAT_40201fcc,500,PTR_s_text_plain_402022fc,PTR_s_BAD_ARGS_40204acc);
    return;
  }
  puVar5 = PTR_DAT_40201358;
  if (0 < *(int *)(PTR_DAT_40201fcc + 0x8c) + *(int *)(PTR_DAT_40201fcc + 0x94)) {
    puVar5 = (undefined *)(*(int *)(PTR_DAT_40201fcc + 0x90) + 0xc);
  }
  FUN_40216114(auStack_34,puVar5);
  iVar3 = FUN_402167d0(auStack_34,PTR_s___3ffe96af_0xe_40201cc8);
  puVar5 = PTR_DAT_40201cd0;
  if (iVar3 == 0) {
    iVar4 = FUN_40213738(PTR_DAT_40201cd0,auStack_34);
    if (iVar4 != 0) {
      FUN_40213754(puVar5,auStack_34);
      FUN_402048f8(puVar1,200,puVar2,PTR_DAT_40201938);
      local_40[0] = iVar3;
      iStack_38 = iVar3;
      FUN_4021612c(auStack_34,local_40);
      FUN_40215e1c(local_40);
      goto LAB_40204c65;
    }
    uVar6 = 0x194;
    puVar5 = PTR_s_FileNotFound_40204bc0;
  }
  else {
    uVar6 = 500;
    puVar5 = PTR_s_BAD_PATH_40204ad0;
  }
  FUN_402048f8(puVar1,uVar6,puVar2,puVar5);
LAB_40204c65:
  FUN_40215e1c(auStack_34);
  return;
}



/* ==== 40204c7c  FUN_40204c7c  size=128 ==== */

void FUN_40204c7c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 ****ppppuVar1;
  undefined4 *puVar2;
  undefined *local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_40;
  undefined4 *puStack_3c;
  undefined4 uStack_38;
  undefined1 uStack_34;
  undefined4 uStack_30;
  undefined4 ****local_2c [2];
  byte bStack_21;
  
  puVar2 = param_4;
  if ((*(byte *)((int)param_4 + 0xb) & 0x80) != 0) {
    puVar2 = (undefined4 *)*param_4;
  }
  uStack_38 = FUN_402226bc(param_4);
  uStack_48 = 1000;
  local_50 = PTR_PTR_40204844;
  uStack_4c = 0;
  uStack_40 = 0;
  uStack_34 = puVar2 <= DAT_402048f4;
  uStack_30 = 0;
  puStack_3c = puVar2;
  FUN_40216000(local_2c,param_3);
  ppppuVar1 = local_2c;
  if ((bStack_21 & 0x80) != 0) {
    ppppuVar1 = local_2c[0];
  }
  FUN_40204848(param_1,param_2,ppppuVar1,&local_50,0);
  FUN_40215e1c(local_2c);
  return;
}



/* ==== 40204d04  FUN_40204d04  size=181 ==== */

void FUN_40204d04(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [36];
  
  puVar1 = PTR_PTR_402032f4;
  *(undefined4 *)(param_1 + 0xac) = param_2;
  FUN_40216338(auStack_38,*(undefined4 *)(puVar1 + 0xb0));
  iVar2 = FUN_402169c4(param_3,auStack_38);
  iVar3 = 0;
  if (iVar2 != 0) {
    FUN_40216338(auStack_44,*(undefined4 *)(puVar1 + 0xb4));
    iVar2 = FUN_402015b8(param_4,auStack_44);
    iVar3 = 0;
    if (iVar2 != 0) {
      FUN_40216338(auStack_50,*(undefined4 *)(puVar1 + 0xbc));
      iVar3 = FUN_402015b8(param_4,auStack_50);
      FUN_40215e1c(auStack_50);
    }
    FUN_40215e1c(auStack_44);
  }
  FUN_40215e1c(auStack_38);
  if (iVar3 != 0) {
    FUN_40216338(auStack_44,PTR_s_Content_Encoding_40204cfc);
    FUN_40216338(auStack_50,PTR_DAT_40204d00);
    FUN_40202de8(param_1,auStack_44,auStack_50,0);
    FUN_40215e1c(auStack_50);
    FUN_40215e1c(auStack_44);
  }
  if ((*(byte *)((int)param_4 + 0xb) & 0x80) != 0) {
    param_4 = (undefined4 *)*param_4;
  }
  FUN_40204c7c(param_1,200,param_4,PTR_DAT_40201358);
  return;
}



/* ==== 40204df8  FUN_40204df8  size=236 ==== */

void FUN_40204df8(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined **ppuVar3;
  int iVar4;
  undefined *puVar5;
  undefined *local_50;
  undefined4 uStack_4c;
  uint uStack_48;
  undefined4 uStack_40;
  undefined *puStack_3c;
  undefined4 uStack_38;
  undefined1 uStack_34;
  undefined4 uStack_30;
  undefined1 auStack_2c [12];
  undefined1 auStack_20 [16];
  
  ppuVar3 = &local_50;
  piVar1 = *(int **)(param_1 + 0x60);
  iVar4 = param_1 + 0x48;
  if ((piVar1 == (int *)0x0) ||
     (iVar2 = (**(code **)(*piVar1 + 0x10))(piVar1,param_1,*(undefined4 *)(param_1 + 0x44),iVar4),
     iVar2 == 0)) {
    if (*(int *)(param_1 + 0x74) == 0) {
      FUN_40216338(&local_50,*(undefined4 *)(PTR_PTR_402032f4 + 4));
      FUN_40216338(auStack_20,PTR_s_Not_found__40204df4);
      FUN_402163d0(auStack_20,iVar4);
      FUN_402160bc(auStack_2c,auStack_20);
      if ((uStack_48 & 0x80000000) != 0) {
        ppuVar3 = (undefined **)local_50;
      }
      FUN_40204c7c(param_1,0x194,ppuVar3,auStack_2c);
      FUN_40215e1c(auStack_2c);
      FUN_40215e1c(auStack_20);
      FUN_40215e1c(&local_50);
    }
    else {
      (*(code *)PTR_FUN_402020f0)(param_1 + 0x6c);
    }
  }
  if (*(char *)(param_1 + 200) != '\0') {
    puVar5 = PTR_DAT_40201358;
    if ((PTR_DAT_40201358[0xb] & 0x80) != 0) {
      puVar5 = *(undefined **)PTR_DAT_40201358;
    }
    uStack_38 = FUN_402226bc();
    uStack_48 = 1000;
    local_50 = PTR_PTR_40204844;
    uStack_4c = 0;
    uStack_40 = 0;
    uStack_34 = puVar5 <= DAT_402048f4;
    uStack_30 = 0;
    puStack_3c = puVar5;
    FUN_402041b0(param_1,&local_50,0);
  }
  FUN_4021614c(iVar4,PTR_DAT_40201938);
  return;
}



/* ==== 40204f08  FUN_40204f08  size=331 ==== */

void FUN_40204f08(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_80 [2];
  undefined4 uStack_78;
  undefined1 auStack_54 [4];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [12];
  undefined1 auStack_2c [12];
  undefined1 auStack_20 [16];
  
  puVar2 = PTR_DAT_40204eec;
  FUN_40216000(local_80,PTR_DAT_40204eec);
  puVar1 = PTR_DAT_40201fcc;
  iVar3 = FUN_40202224(PTR_DAT_40201fcc,local_80);
  FUN_40215e1c(local_80);
  if (iVar3 == 0) {
    FUN_402048f8(puVar1,500,PTR_s_text_plain_402022fc,PTR_s_BAD_ARGS_40204acc);
  }
  else {
    FUN_40216000(local_80,puVar2);
    uVar4 = FUN_402023fc(puVar1,local_80);
    FUN_40216114(auStack_20,uVar4);
    FUN_40215e1c(local_80);
    FUN_402137f4(auStack_54,PTR_DAT_40201cd0,auStack_20);
    local_80[0] = 0;
    uStack_78 = 0;
    FUN_4021612c(auStack_20,local_80);
    FUN_40215e1c(local_80);
    puVar2 = PTR_DAT_40204ef0;
    FUN_40216000(auStack_2c,PTR_DAT_40204ef0);
    while (iVar3 = FUN_402231e0(auStack_54), iVar3 != 0) {
      FUN_402138d8(local_80,auStack_54,PTR_s_r_3ffe959f_0xa_40201e18);
      iVar3 = FUN_402167d0(auStack_2c,puVar2);
      if (iVar3 == 0) {
        FUN_4021649c(auStack_2c,0x2c);
      }
      FUN_4021646c(auStack_2c,PTR_s___type____40204ef4);
      FUN_4021646c(auStack_2c,DAT_40204ef8);
      FUN_4021646c(auStack_2c,PTR_s____name____40204efc);
      uVar4 = FUN_40223184(local_80);
      FUN_40216000(auStack_44,uVar4);
      FUN_40201628(auStack_38,auStack_44,1);
      FUN_402163d0(auStack_2c,auStack_38);
      FUN_40215e1c(auStack_38);
      FUN_40215e1c(auStack_44);
      FUN_4021646c(auStack_2c,PTR_DAT_40201f24);
      FUN_40213968(local_80);
      FUN_40201ca0(local_80);
    }
    FUN_4021646c(auStack_2c,DAT_40204f00);
    FUN_40204c7c(puVar1,200,PTR_s_text_json_40204f04,auStack_2c);
    FUN_40215e1c(auStack_2c);
    FUN_402226f4(auStack_50);
    FUN_40215e1c(auStack_20);
  }
  return;
}



/* ==== 4020507c  FUN_4020507c  size=482 ==== */

undefined4 FUN_4020507c(undefined4 param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 **ppuVar7;
  undefined1 *local_a0 [2];
  byte bStack_95;
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  undefined1 auStack_5c [12];
  undefined4 auStack_50 [2];
  undefined4 uStack_48;
  undefined1 auStack_44 [20];
  int iStack_30;
  
  puVar1 = PTR_PTR_40205058;
  puVar2 = PTR_DAT_40201fcc;
  iVar4 = FUN_40202b6c(PTR_DAT_40201fcc,*(undefined4 *)PTR_PTR_4020505c,
                       *(undefined4 *)PTR_PTR_40205058);
  if (iVar4 == 0) {
    iStack_30 = iVar4;
    FUN_40216000(auStack_44,PTR_DAT_40201938);
    FUN_40216338(local_a0,PTR_s_Login_Required_40205060);
    puVar3 = PTR_DAT_40205064;
    FUN_4021612c(PTR_DAT_40205064,local_a0);
    FUN_40215e1c(local_a0);
    FUN_40216338(local_a0,PTR_s_WWW_Authenticate_40205068);
    FUN_40216338(auStack_5c,PTR_s_Basic_realm___4020506c);
    FUN_402163d0(auStack_5c,puVar3);
    FUN_402160bc(auStack_68,auStack_5c);
    auStack_50[0] = 0x22;
    uStack_48 = DAT_40205070;
    FUN_40216644(auStack_74,auStack_68,auStack_50);
    FUN_40202de8(puVar2,local_a0,auStack_74,iStack_30);
    FUN_40215e1c(auStack_74);
    FUN_40215e1c(auStack_50);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40215e1c(local_a0);
    FUN_40216338(local_a0,*(undefined4 *)(PTR_PTR_402032f4 + 4));
    ppuVar7 = local_a0;
    if ((bStack_95 & 0x80) != 0) {
      ppuVar7 = (undefined1 **)local_a0[0];
    }
    FUN_40204c7c(puVar2,0x191,ppuVar7,auStack_44);
    FUN_40215e1c(local_a0);
    FUN_40215e1c(auStack_44);
    FUN_4021836c(500);
    iVar4 = FUN_40202b6c(puVar2,*(undefined4 *)PTR_PTR_4020505c,*(undefined4 *)puVar1);
    if (iVar4 == 0) {
      return 0;
    }
  }
  iVar4 = FUN_402015fc(param_1,PTR_s___3ffe96af_0xe_40201cc8);
  if (iVar4 != 0) {
    FUN_4021646c(param_1,PTR_s_index_htm_40205074);
  }
  FUN_40216114(local_a0,param_1);
  FUN_40202300(auStack_5c,local_a0);
  FUN_40215e1c(local_a0);
  FUN_40216114(auStack_68,param_1);
  puVar3 = PTR_DAT_402022f4;
  FUN_4021646c(auStack_68,PTR_DAT_402022f4);
  puVar1 = PTR_DAT_40201cd0;
  iVar4 = FUN_40213738(PTR_DAT_40201cd0,auStack_68);
  if (iVar4 == 0) {
    iVar4 = FUN_40213738(puVar1,param_1);
    uVar5 = 0;
    if (iVar4 == 0) goto LAB_4020523a;
  }
  iVar4 = FUN_40213738(puVar1,auStack_68);
  if (iVar4 != 0) {
    FUN_4021646c(param_1,puVar3);
  }
  FUN_402138b4(local_a0,puVar1,param_1,PTR_s_r_3ffe959f_0xa_40201e18);
  uVar5 = FUN_4022315c(local_a0);
  uVar6 = FUN_40223184(local_a0);
  FUN_40216000(auStack_74,uVar6);
  FUN_40204d04(puVar2,uVar5,auStack_74,auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215444(local_a0,PTR_DAT_40205078,0xffffffff,0xffffffff);
  FUN_40213968(local_a0);
  FUN_40201ca0(local_a0);
  uVar5 = 1;
LAB_4020523a:
  iStack_30 = uVar5;
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  return iStack_30;
}



/* ==== 40205264  FUN_40205264  size=53 ==== */

void FUN_40205264(void)

{
  int iVar1;
  undefined1 auStack_20 [24];
  
  FUN_40216114(auStack_20,PTR_DAT_40201fc8);
  iVar1 = FUN_4020507c(auStack_20);
  FUN_40215e1c(auStack_20);
  if (iVar1 == 0) {
    FUN_402048f8(PTR_DAT_40201fcc,0x194,PTR_s_text_plain_402022fc,PTR_s_FileNotFound_40204bc0);
  }
  return;
}



/* ==== 402052a0  FUN_402052a0  size=53 ==== */

void FUN_402052a0(void)

{
  int iVar1;
  undefined1 auStack_20 [24];
  
  FUN_40216000(auStack_20,PTR_s__edit_htm_4020529c);
  iVar1 = FUN_4020507c(auStack_20);
  FUN_40215e1c(auStack_20);
  if (iVar1 == 0) {
    FUN_402048f8(PTR_DAT_40201fcc,0x194,PTR_s_text_plain_402022fc,PTR_s_FileNotFound_40204bc0);
  }
  return;
}



/* ==== 402052dc  FUN_402052dc  size=73 ==== */

int FUN_402052dc(int param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = *(uint *)(param_1 + 0xc);
  if (*(uint *)(param_1 + 0xc) < param_2) {
    uVar4 = param_2;
  }
  puVar1 = (undefined4 *)(*(code *)PTR_FUN_402052d8)(uVar4 + 0xc);
  iVar3 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = 0;
    uVar2 = *(undefined4 *)(param_1 + 8);
    puVar1[1] = uVar4;
    *puVar1 = uVar2;
    *(undefined4 **)(param_1 + 8) = puVar1;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) * 2;
    iVar3 = puVar1[2];
    puVar1[2] = param_2 + iVar3;
    iVar3 = (int)puVar1 + iVar3 + 0xc;
  }
  return iVar3;
}



/* ==== 40205328  FUN_40205328  size=46 ==== */

int FUN_40205328(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  if (iVar2 != 0) {
    uVar1 = *(int *)(iVar2 + 8) + 3U & 0xfffffffc;
    *(uint *)(iVar2 + 8) = uVar1;
    if (param_2 + uVar1 <= *(uint *)(iVar2 + 4)) {
      *(uint *)(iVar2 + 8) = param_2 + uVar1;
      return iVar2 + 0xc + uVar1;
    }
  }
  iVar2 = FUN_402052dc();
  return iVar2;
}



/* ==== 40205358  FUN_40205358  size=112 ==== */

void FUN_40205358(int *param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = *(int *)(*param_1 + 8);
  if (iVar2 != 0) {
    iVar4 = *(int *)(iVar2 + 8);
    uVar3 = iVar4 + 1;
    if (uVar3 <= *(uint *)(iVar2 + 4)) {
      *(uint *)(iVar2 + 8) = uVar3;
      puVar1 = (undefined1 *)(iVar2 + 0xc + iVar4);
      *puVar1 = param_2;
      if (param_1[2] == 0) {
        param_1[1] = (int)puVar1;
      }
      goto LAB_402053b8;
    }
  }
  iVar2 = FUN_402052dc(*param_1,param_1[2] + 1);
  if (param_1[1] == 0) {
    if (iVar2 != 0) {
LAB_402053af:
      *(undefined1 *)(iVar2 + param_1[2]) = param_2;
    }
  }
  else if (iVar2 != 0) {
    iVar2 = (*(code *)PTR_FUN_402014c0)(iVar2,param_1[1],param_1[2]);
    goto LAB_402053af;
  }
  param_1[1] = iVar2;
LAB_402053b8:
  param_1[2] = param_1[2] + 1;
  return;
}



/* ==== 402053d4  FUN_402053d4  size=214 ==== */

undefined4 FUN_402053d4(int param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  char cVar4;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  local_30 = *(undefined4 *)(param_1 + 8);
  uStack_2c = 0;
  uStack_28 = 0;
  FUN_40222834(param_1 + 4);
  cVar4 = **(char **)(param_1 + 4);
  if ((cVar4 != '\'') && (cVar4 != '\"')) {
    while ((((byte)(cVar4 + 0xa1U) < 0x1c || ((byte)(cVar4 + 0xbfU) < 0x1a)) ||
           (((byte)(cVar4 - 0x2bU) < 0xf && ((DAT_402053d0 & 1 << (cVar4 - 0x2bU & 0x1f)) != 0)))))
    {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      FUN_40205358(&local_30,cVar4);
      cVar4 = **(char **)(param_1 + 4);
    }
LAB_40205494:
    FUN_40205358(&local_30,0);
    return uStack_2c;
  }
  *(char **)(param_1 + 4) = *(char **)(param_1 + 4) + 1;
  do {
    pcVar1 = *(char **)(param_1 + 4);
    cVar2 = *pcVar1;
    if ((cVar2 == '\0') || (*(char **)(param_1 + 4) = pcVar1 + 1, cVar4 == cVar2))
    goto LAB_40205494;
    if (cVar2 == '\\') {
      cVar2 = pcVar1[1];
      for (pcVar3 = PTR_DAT_402053cc; *pcVar3 != '\0'; pcVar3 = pcVar3 + 2) {
        if (cVar2 == *pcVar3) {
          cVar2 = pcVar3[1];
          break;
        }
      }
      if (cVar2 == '\0') goto LAB_40205494;
      *(char **)(param_1 + 4) = pcVar1 + 2;
    }
    FUN_40205358(&local_30);
  } while( true );
}



/* ==== 402054b0  FUN_402054b0  size=193 ==== */

undefined4 * FUN_402054b0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  int local_30;
  undefined4 uStack_2c;
  
  if (*(char *)(param_1 + 3) != '\0') {
    uVar7 = *param_1;
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + -1;
    puVar4 = (undefined4 *)FUN_402226d8(8,uVar7);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)FUN_402016f0();
    }
    else {
      *puVar4 = uVar7;
      puVar4[1] = 0;
    }
    puVar8 = param_1 + 1;
    iVar1 = FUN_40204220(puVar8,0x5b);
    if (iVar1 != 0) {
      iVar1 = FUN_40204220(puVar8,0x5d);
      if (iVar1 != 0) {
LAB_40205548:
        *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
        return puVar4;
      }
      do {
        local_30 = iVar1;
        iVar2 = FUN_40205578(param_1,&local_30);
        if (iVar2 == 0) break;
        puVar3 = (undefined4 *)FUN_402226d8(0xc,*puVar4);
        if (puVar3 != (undefined4 *)0x0) {
          *puVar3 = 0;
          puVar3[1] = 0;
        }
        puVar6 = (undefined4 *)puVar4[1];
        if ((undefined4 *)puVar4[1] == (undefined4 *)0x0) {
          puVar4[1] = puVar3;
        }
        else {
          do {
            puVar5 = puVar6;
            puVar6 = (undefined4 *)*puVar5;
          } while (puVar6 != (undefined4 *)0x0);
          *puVar5 = puVar3;
        }
        if (puVar3 == (undefined4 *)0x0) break;
        puVar3[2] = uStack_2c;
        puVar3[1] = local_30;
        iVar2 = FUN_40204220(puVar8,0x5d);
        if (iVar2 != 0) goto LAB_40205548;
        iVar2 = FUN_40204220(puVar8,0x2c);
      } while (iVar2 != 0);
    }
  }
  puVar4 = (undefined4 *)FUN_402016f0();
  return puVar4;
}



/* ==== 40205578  FUN_40205578  size=153 ==== */

bool FUN_40205578(int param_1,undefined4 *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  FUN_40222834(param_1 + 4);
  cVar1 = **(char **)(param_1 + 4);
  if (cVar1 == '[') {
    piVar2 = (int *)FUN_402054b0(param_1);
    if (*piVar2 != 0) {
      uVar4 = 6;
LAB_402055c9:
      *param_2 = uVar4;
      param_2[1] = piVar2;
      return true;
    }
  }
  else if (cVar1 == '{') {
    piVar2 = (int *)FUN_40205614(param_1);
    if (*piVar2 != 0) {
      uVar4 = 7;
      goto LAB_402055c9;
    }
  }
  else {
    iVar3 = FUN_402053d4(param_1);
    if (iVar3 != 0) {
      if (cVar1 == '\'' || cVar1 == '\"') {
        *param_2 = 2;
        param_2[1] = iVar3;
        return cVar1 == '\'' || cVar1 == '\"';
      }
      *param_2 = 1;
      param_2[1] = iVar3;
      return true;
    }
  }
  return false;
}



/* ==== 40205614  FUN_40205614  size=233 ==== */

undefined4 * FUN_40205614(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int local_40;
  int iStack_3c;
  int iStack_30;
  int *piStack_2c;
  
  if (*(char *)(param_1 + 3) != '\0') {
    uVar5 = *param_1;
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + -1;
    puVar3 = (undefined4 *)FUN_402226d8(8,uVar5);
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)FUN_40201738();
    }
    else {
      *puVar3 = uVar5;
      puVar3[1] = 0;
    }
    puVar6 = param_1 + 1;
    iVar1 = FUN_40204220(puVar6,0x7b);
    if (iVar1 != 0) {
      iStack_30 = FUN_40204220(puVar6,0x7d);
      if (iStack_30 != 0) {
LAB_402056c8:
        *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
        return puVar3;
      }
      do {
        iVar1 = FUN_402053d4(param_1);
        if ((iVar1 == 0) || (iVar2 = FUN_40204220(puVar6,0x3a), iVar2 == 0)) break;
        local_40 = iStack_30;
        iVar2 = FUN_40205578(param_1,&local_40);
        if (iVar2 == 0) break;
        for (piVar4 = (int *)puVar3[1]; piVar4 != (int *)0x0; piVar4 = (int *)*piVar4) {
          if ((piVar4[1] != 0) &&
             (piStack_2c = piVar4, iVar2 = (*(code *)PTR_FUN_40204250)(iVar1), piVar4 = piStack_2c,
             iVar2 == 0)) goto LAB_402056a5;
        }
        piVar4 = (int *)FUN_402042b0(puVar3);
        if (piVar4 == (int *)0x0) break;
        piVar4[1] = iVar1;
LAB_402056a5:
        piVar4[3] = iStack_3c;
        piVar4[2] = local_40;
        iVar1 = FUN_40204220(puVar6,0x7d);
        if (iVar1 != 0) goto LAB_402056c8;
        iVar1 = FUN_40204220(puVar6,0x2c);
      } while (iVar1 != 0);
    }
  }
  puVar3 = (undefined4 *)FUN_40201738();
  return puVar3;
}



/* ==== 40205708  FUN_40205708  size=45 ==== */

void FUN_40205708(undefined4 param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined4 local_20;
  undefined4 *puStack_1c;
  undefined4 uStack_18;
  undefined1 uStack_14;
  
  if (((*(byte *)((int)param_2 + 0xb) & 0x80) != 0) &&
     (param_2 = (undefined4 *)*param_2, param_2 == (undefined4 *)0x0)) {
    param_2 = (undefined4 *)PTR_DAT_40201938;
  }
  local_20 = param_1;
  puStack_1c = param_2;
  uStack_18 = param_1;
  uStack_14 = param_3;
  FUN_40205614(&local_20);
  return;
}



/* ==== 40205740  FUN_40205740  size=182 ==== */

int FUN_40205740(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  undefined *local_20 [2];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  local_20[0] = PTR_PTR_40205738;
  bVar2 = false;
  uStack_14 = 0x100;
  uStack_18 = 0;
  uVar3 = FUN_40205708(local_20,param_1,10);
  iVar4 = FUN_40204254(uVar3,param_2);
  iVar6 = 0;
  if (iVar4 == 0) goto LAB_402057e6;
  uVar7 = *(uint *)(iVar4 + 8);
  if (uVar7 < 5) {
    if (2 < uVar7) {
      iVar6 = *(int *)(iVar4 + 0xc);
      goto LAB_402057e6;
    }
    iVar6 = 0;
    if (uVar7 == 0) goto LAB_402057e6;
    pbVar5 = *(byte **)(iVar4 + 0xc);
    if (pbVar5 == (byte *)0x0) {
      iVar6 = 0;
      goto LAB_402057e6;
    }
    bVar1 = *pbVar5;
    iVar6 = 1;
    if (bVar1 == 0x74) goto LAB_402057e6;
    if (bVar1 == 0x2b) {
      pbVar5 = pbVar5 + 1;
    }
    else if (bVar1 == 0x2d) {
      pbVar5 = pbVar5 + 1;
      bVar2 = true;
    }
    iVar6 = 0;
    while( true ) {
      if (9 < (*pbVar5 - 0x30 & 0xff)) break;
      iVar6 = iVar6 * 10 + (uint)*pbVar5 + -0x30;
      pbVar5 = pbVar5 + 1;
    }
    if (!bVar2) goto LAB_402057e6;
  }
  else {
    if (uVar7 != 5) {
      iVar6 = (*(code *)PTR_FUN_4020573c)(*(undefined4 *)(iVar4 + 0xc));
      goto LAB_402057e6;
    }
    iVar6 = *(int *)(iVar4 + 0xc);
  }
  iVar6 = -iVar6;
LAB_402057e6:
  FUN_402024b0(local_20);
  return iVar6;
}



/* ==== 402057fc  json_read_int  size=173 ==== */

int json_read_int(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  undefined *local_20 [2];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  local_20[0] = PTR_PTR_40205738;
  bVar2 = false;
  uStack_14 = 0x100;
  uStack_18 = 0;
  uVar3 = FUN_40205708(local_20,param_1,10);
  iVar4 = FUN_40204254(uVar3,param_2);
  iVar7 = 0;
  if (iVar4 == 0) goto LAB_40205899;
  uVar6 = *(uint *)(iVar4 + 8);
  if (uVar6 < 5) {
    if (2 < uVar6) {
      iVar7 = *(int *)(iVar4 + 0xc);
      goto LAB_40205899;
    }
    if ((uVar6 == 0) || (pbVar5 = *(byte **)(iVar4 + 0xc), pbVar5 == (byte *)0x0))
    goto LAB_40205899;
    bVar1 = *pbVar5;
    iVar7 = 1;
    if (bVar1 == 0x74) goto LAB_40205899;
    if (bVar1 == 0x2b) {
      pbVar5 = pbVar5 + 1;
    }
    else if (bVar1 == 0x2d) {
      pbVar5 = pbVar5 + 1;
      bVar2 = true;
    }
    iVar7 = 0;
    while ((*pbVar5 - 0x30 & 0xff) < 10) {
      iVar7 = iVar7 * 10 + (*pbVar5 - 0x30);
      pbVar5 = pbVar5 + 1;
    }
    if (!bVar2) goto LAB_40205899;
  }
  else {
    if (uVar6 != 5) {
      iVar7 = FUN_4022e648(*(undefined4 *)(iVar4 + 0xc));
      goto LAB_40205899;
    }
    iVar7 = *(int *)(iVar4 + 0xc);
  }
  iVar7 = -iVar7;
LAB_40205899:
  FUN_402024b0(local_20);
  return iVar7;
}



/* ==== 402058d0  adc_dac_setup  size=156 ==== */

void adc_dac_setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined1 uVar3;
  undefined *local_30 [2];
  undefined *puStack_28;
  undefined *puStack_24;
  undefined *apuStack_20 [2];
  undefined *puStack_18;
  undefined *puStack_14;
  
  FUN_40212b08(PTR_DAT_402058ac);
  FUN_40216000(local_30,PTR_s_maxSpeed_3ffe8c63_1_402058b0);
  uVar3 = json_read_int(PTR_DAT_40201dd8,local_30);
  *PTR_DAT_402058b4 = uVar3;
  FUN_40215e1c(local_30);
  FUN_402016cc(apuStack_20,PTR_s__maxSpeed_402058b8);
  puVar2 = PTR_LAB_40202ed4;
  puVar1 = PTR_FUN_40202ed0;
  local_30[0] = PTR_FUN_402058bc;
  puStack_24 = PTR_FUN_40202ed0;
  puStack_28 = PTR_LAB_40202ed4;
  FUN_40202478(PTR_DAT_40201fcc,apuStack_20,local_30);
  FUN_402226a4(local_30);
  FUN_40201070(apuStack_20);
  apuStack_20[0] = PTR_FUN_402058c0;
  puStack_28 = (undefined *)0x0;
  puStack_14 = puVar1;
  puStack_18 = puVar2;
  FUN_40202e74(apuStack_20,local_30);
  FUN_40202e74(local_30,PTR_DAT_402058c4);
  FUN_402226a4(local_30);
  FUN_4020fb94(PTR_DAT_402058c8,0x1e,1,PTR_FUN_402058cc,PTR_DAT_402058c8);
  FUN_402226a4(apuStack_20);
  return;
}



/* ==== 40205974  FUN_40205974  size=51 ==== */

void FUN_40205974(void)

{
  undefined1 auStack_20 [28];
  
  FUN_40216000(auStack_20,PTR_s_timezone_4020596c);
  json_read_int(PTR_DAT_40201dd8,auStack_20);
  FUN_40201a3c();
  FUN_40215e1c(auStack_20);
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 402059b8  time_setup  size=177 ==== */

void time_setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *local_40 [2];
  undefined *puStack_38;
  undefined *puStack_34;
  undefined1 auStack_30 [28];
  
  puVar4 = PTR_s_timezone_4020596c;
  FUN_40216000(local_40,PTR_s_timezone_4020596c);
  puVar1 = PTR_DAT_40201dd8;
  json_read_int(PTR_DAT_40201dd8,local_40);
  FUN_40201a3c();
  FUN_40215e1c(local_40);
  FUN_402016cc(auStack_30,PTR_s__Time_402059a8);
  puVar3 = PTR_FUN_40202ed0;
  puVar2 = PTR_DAT_40201fcc;
  local_40[0] = PTR_FUN_402059ac;
  puStack_38 = PTR_LAB_40202ed4;
  puStack_34 = PTR_FUN_40202ed0;
  FUN_40202478(PTR_DAT_40201fcc,auStack_30,local_40);
  FUN_402226a4(local_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__timeZone_402059b0);
  local_40[0] = PTR_FUN_402059b4;
  puStack_38 = PTR_LAB_40202ed4;
  puStack_34 = puVar3;
  FUN_40202478(puVar2,auStack_30,local_40);
  FUN_402226a4(local_40);
  FUN_40201070(auStack_30);
  FUN_4021836c(1000);
  FUN_40216000(local_40,puVar4);
  json_read_int(puVar1,local_40);
  FUN_40201a3c();
  FUN_40215e1c(local_40);
  return;
}



/* ==== 40205a6c  FUN_40205a6c  size=91 ==== */

undefined4 FUN_40205a6c(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((*(byte *)((int)param_1 + 0xb) & 0x80) == 0) || (*param_1 != 0)) {
    iVar1 = FUN_402226bc(param_1);
    iVar2 = (**(code **)*param_2)(param_2,iVar1 + 1);
    if (iVar2 != 0) {
      if ((*(byte *)((int)param_1 + 0xb) & 0x80) != 0) {
        param_1 = (int *)*param_1;
      }
      uVar3 = (*(code *)PTR_FUN_402014c0)(iVar2,param_1,iVar1 + 1);
      return uVar3;
    }
  }
  return 0;
}



/* ==== 40205ac8  FUN_40205ac8  size=68 ==== */

int FUN_40205ac8(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_402228a4(param_3);
  if (iVar1 == 0) {
    iVar2 = FUN_40205a6c(param_3,param_1);
    if (iVar2 != 0) {
      *param_2 = iVar2;
      iVar1 = 1;
    }
  }
  else {
    *param_2 = 0;
  }
  return iVar1;
}



/* ==== 40205b10  FUN_40205b10  size=37 ==== */

void FUN_40205b10(undefined4 *param_1,undefined1 param_2)

{
  FUN_4021649c(*(undefined4 *)*param_1,param_2);
  param_1[1] = param_1[1] + 1;
  return;
}



/* ==== 40205b38  FUN_40205b38  size=65 ==== */

void FUN_40205b38(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  puVar3 = (undefined4 *)*param_1;
  uVar4 = *puVar3;
  iVar1 = FUN_402226bc(uVar4);
  FUN_4021646c(uVar4,param_2);
  iVar2 = FUN_402226bc(*puVar3);
  param_1[1] = (iVar2 + param_1[1]) - iVar1;
  return;
}



/* ==== 40205b84  FUN_40205b84  size=104 ==== */

void FUN_40205b84(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  char cVar3;
  
  cVar3 = '\"';
  if (param_2 == (char *)0x0) {
    FUN_40205b38(param_1,PTR_DAT_40205b80);
  }
  else {
LAB_40205ba4:
    FUN_40205b10(param_1,cVar3);
    cVar3 = *param_2;
    if (cVar3 != '\0') {
      param_2 = param_2 + 1;
      for (pcVar2 = PTR_DAT_40205b7c; cVar1 = *pcVar2, cVar1 != '\0'; pcVar2 = pcVar2 + 2) {
        if (pcVar2[1] == cVar3) {
          FUN_40205b10(param_1,0x5c);
          cVar3 = cVar1;
          break;
        }
      }
      goto LAB_40205ba4;
    }
    FUN_40205b10(param_1,0x22);
  }
  return;
}



/* ==== 40205c2c  FUN_40205c2c  size=482 ==== */

void FUN_40205c2c(uint *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  char local_30;
  
  uVar6 = DAT_40205bf4;
  *(undefined1 *)((int)param_1 + 10) = 6;
  iVar2 = FUN_4022e888(param_2,uVar6);
  if (iVar2 < 0) {
    iVar10 = 0x20;
    local_30 = '\x05';
    iVar2 = 0;
  }
  else {
    iVar8 = 0x14;
    iVar2 = 0;
    iVar10 = 0x20;
    do {
      iVar3 = FUN_4022e83c(*(undefined4 *)(PTR_DAT_40205bf8 + iVar8),param_2);
      if (iVar3 < 1) {
        param_2 = (*(code *)PTR_FUN_40205c10)(param_2,*(undefined4 *)(PTR_DAT_40205bfc + iVar8));
        iVar2 = (iVar10 + iVar2) * 0x10000 >> 0x10;
      }
      iVar8 = iVar8 + -4;
      iVar10 = iVar10 >> 1;
    } while (iVar8 != -4);
    local_30 = -1;
  }
  iVar8 = FUN_4022e81c(param_2,DAT_40205c00);
  if (0 < iVar8) {
    uVar11 = (*(code *)PTR_FUN_40205c14)(param_2);
    iVar8 = FUN_4022e6dc((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),DAT_40205c04,DAT_40205c08);
    if (iVar8 < 1) {
      for (uVar9 = (uint)local_30; (uVar9 & 0x80) == 0; uVar9 = uVar9 - 1) {
        iVar8 = FUN_4022e81c(*(undefined4 *)(PTR_DAT_40205c0c + uVar9 * 4),param_2);
        if (0 < iVar8) {
          param_2 = (*(code *)PTR_FUN_40205c10)
                              (param_2,*(undefined4 *)(PTR_DAT_40205bf8 + uVar9 * 4));
          iVar2 = (iVar2 - iVar10) * 0x10000 >> 0x10;
        }
        iVar10 = iVar10 >> 1;
      }
    }
  }
  *(short *)(param_1 + 2) = (short)iVar2;
  uVar4 = (*(code *)PTR_FUN_4020573c)(param_2);
  uVar9 = DAT_40205bf0;
  *param_1 = uVar4;
  for (uVar5 = uVar4; 9 < uVar5; uVar5 = (*(code *)PTR_FUN_40205c18)(uVar5,10)) {
    uVar9 = (*(code *)PTR_FUN_40205c18)(uVar9,10);
    *(char *)((int)param_1 + 10) = *(char *)((int)param_1 + 10) + -1;
  }
  uVar6 = (*(code *)PTR_FUN_40205c1c)(uVar4);
  uVar6 = (*(code *)PTR_FUN_40205c20)(param_2,uVar6);
  uVar7 = (*(code *)PTR_FUN_40205c1c)(uVar9);
  uVar6 = (*(code *)PTR_FUN_40205c10)(uVar6,uVar7);
  iVar10 = (*(code *)PTR_FUN_4020573c)();
  uVar7 = (*(code *)PTR_FUN_40205c1c)();
  uVar6 = (*(code *)PTR_FUN_40205c20)(uVar6,uVar7);
  (*(code *)PTR_FUN_40205c24)(uVar6,uVar6);
  iVar8 = (*(code *)PTR_FUN_4020573c)();
  if ((uint)(iVar8 + iVar10) < uVar9) {
    param_1[1] = iVar8 + iVar10;
  }
  else {
    param_1[1] = 0;
    *param_1 = uVar4 + 1;
    if ((iVar2 != 0) && (9 < uVar4 + 1)) {
      *(short *)(param_1 + 2) = (short)iVar2 + 1;
      *param_1 = 1;
    }
  }
  while( true ) {
    uVar9 = param_1[1];
    iVar2 = (*(code *)PTR_FUN_40205c28)(uVar9,10);
    if ((iVar2 != 0) || (cVar1 = *(char *)((int)param_1 + 10), cVar1 < '\x01')) break;
    uVar9 = (*(code *)PTR_FUN_40205c18)(uVar9,10);
    param_1[1] = uVar9;
    *(char *)((int)param_1 + 10) = cVar1 + -1;
  }
  return;
}



/* ==== 40205e28  FUN_40205e28  size=433 ==== */

void FUN_40205e28(undefined4 param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  char *pcVar8;
  char local_52 [6];
  char local_4c [4];
  uint uStack_48;
  uint uStack_44;
  short sStack_40;
  byte bStack_3e;
  uint uStack_30;
  uint uStack_2c;
  char *pcStack_28;
  
  iVar2 = FUN_4022e7f4(param_2);
  uVar3 = DAT_40205c00;
  pcVar6 = PTR_DAT_40205e14;
  if (iVar2 == 0) {
    iVar2 = FUN_4022e8a8(param_2,DAT_40205c00);
    if (iVar2 < 0) {
      FUN_40205b10(param_1,0x2d);
      param_2 = param_2 ^ 0x80000000;
    }
    iVar2 = FUN_4022e7f4(param_2,uVar3);
    if (iVar2 != 0) {
      uVar3 = (*(code *)PTR_FUN_40205c24)(param_2,param_2);
      iVar2 = FUN_4022e7f4(param_2,uVar3);
      pcVar6 = PTR_s_Infinity_40205e18;
      if (iVar2 == 0) goto LAB_40205fc0;
    }
    FUN_40205c2c(&uStack_48,param_2);
    local_4c[1] = 0;
    pcVar6 = local_4c + 1;
    uStack_30 = 9;
    do {
      cVar1 = (*(code *)PTR_FUN_40205c28)(uStack_48,10);
      pcVar6 = pcVar6 + -1;
      *pcVar6 = cVar1 + '0';
      uStack_2c = uStack_48;
      uStack_48 = (*(code *)PTR_FUN_40205c18)(uStack_48,10);
    } while (uStack_30 < uStack_2c);
    FUN_40205b38(param_1,pcVar6);
    uVar7 = (uint)bStack_3e;
    if (uVar7 != 0) {
      pcVar8 = local_52 + 1;
      local_52[1] = 0;
      pcVar6 = pcVar8;
      uVar5 = uVar7;
      while( true ) {
        pcVar8 = pcVar8 + -1;
        if ((int)((uVar5 - 1) * 0x1000000) >> 0x18 == -1) break;
        uStack_30 = uVar5 - 1 & 0xff;
        uStack_2c = uStack_44;
        pcStack_28 = pcVar6;
        cVar1 = (*(code *)PTR_FUN_40205c28)(uStack_44,10);
        *pcVar8 = cVar1 + '0';
        uStack_44 = (*(code *)PTR_FUN_40205c18)(uStack_2c,10);
        pcVar6 = pcStack_28;
        uVar5 = uStack_30;
      }
      pcVar6[-1 - uVar7] = '.';
      FUN_40205b38(param_1,pcVar6 + (uVar7 ^ 0xffffffff));
    }
    if (sStack_40 < 0) {
      FUN_40205b38(param_1,PTR_DAT_40205e1c);
      iVar2 = -(int)sStack_40;
      local_4c[1] = 0;
      pcVar6 = local_4c + 1;
      do {
        cVar1 = (*(code *)PTR_FUN_40205e20)(iVar2,10);
        pcVar6 = pcVar6 + -1;
        *pcVar6 = cVar1 + '0';
        iVar2 = (*(code *)PTR_FUN_40205e24)(iVar2,10);
      } while (iVar2 != 0);
      FUN_40205b38(param_1,pcVar6);
    }
    if (sStack_40 < 1) {
      return;
    }
    FUN_40205b10(param_1,0x65);
    iVar2 = (int)sStack_40;
    local_4c[1] = 0;
    pcVar6 = local_4c + 1;
    do {
      cVar1 = (*(code *)PTR_FUN_40205e20)(iVar2,10);
      pcVar6 = pcVar6 + -1;
      *pcVar6 = cVar1 + '0';
      iVar4 = (*(code *)PTR_FUN_40205e24)(iVar2,10);
      iVar2 = (iVar4 << 0x10) >> 0x10;
    } while (iVar4 << 0x10 != 0);
  }
LAB_40205fc0:
  FUN_40205b38(param_1,pcVar6);
  return;
}



/* ==== 40205fe8  FUN_40205fe8  size=231 ==== */

void FUN_40205fe8(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  uint uVar5;
  char local_3c [12];
  uint uStack_30;
  uint uStack_2c;
  
  switch(*param_1) {
  case 1:
    pcVar4 = (char *)param_1[1];
    goto LAB_402060e0;
  case 2:
    FUN_40205b84(param_2,param_1[1]);
    break;
  case 3:
    pcVar4 = PTR_DAT_40205fdc;
    if (param_1[1] == 0) {
      pcVar4 = PTR_s_false_40205fe0;
    }
    goto LAB_402060e0;
  case 5:
    FUN_40205b10(param_2,0x2d);
  case 4:
    uVar5 = param_1[1];
    local_3c[1] = 0;
    pcVar4 = local_3c + 1;
    uStack_2c = 9;
    do {
      cVar1 = (*(code *)PTR_FUN_40205c28)(uVar5,10);
      pcVar4 = pcVar4 + -1;
      *pcVar4 = cVar1 + '0';
      uStack_30 = uVar5;
      uVar5 = (*(code *)PTR_FUN_40205c18)(uVar5,10);
    } while (uStack_2c < uStack_30);
LAB_402060e0:
    FUN_40205b38(param_2,pcVar4);
    break;
  case 6:
    iVar2 = param_1[1];
    FUN_40205b10(param_2,0x5b);
    piVar3 = *(int **)(iVar2 + 4);
    while (piVar3 != (int *)0x0) {
      FUN_40205fe8(piVar3 + 1,param_2);
      piVar3 = (int *)*piVar3;
      if (piVar3 == (int *)0x0) break;
      FUN_40205b10(param_2,0x2c);
    }
    FUN_40205b10(param_2,0x5d);
    break;
  case 7:
    FUN_402060fc(param_1[1],param_2);
    break;
  case 8:
    FUN_40205e28(param_2,param_1[1]);
  }
  return;
}



/* ==== 402060fc  FUN_402060fc  size=85 ==== */

void FUN_402060fc(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  FUN_40205b10(param_2,0x7b);
  piVar1 = *(int **)(param_1 + 4);
  while (piVar1 != (int *)0x0) {
    FUN_40205b84(param_2,piVar1[1]);
    FUN_40205b10(param_2,0x3a);
    FUN_40205fe8(piVar1 + 2,param_2);
    piVar1 = (int *)*piVar1;
    if (piVar1 == (int *)0x0) break;
    FUN_40205b10(param_2,0x2c);
  }
  FUN_40205b10(param_2,0x7d);
  return;
}



/* ==== 40206154  FUN_40206154  size=27 ==== */

void FUN_40206154(undefined4 param_1,undefined4 param_2)

{
  undefined4 *local_20;
  undefined4 uStack_1c;
  undefined4 auStack_18 [5];
  
  local_20 = auStack_18;
  uStack_1c = 0;
  auStack_18[0] = param_2;
  FUN_402060fc(param_1,&local_20);
  return;
}



/* ==== 40206170  FUN_40206170  size=141 ==== */

undefined4 FUN_40206170(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  uStack_30 = param_4;
  puVar1 = (undefined4 *)FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_402228a4(param_3);
  if (iVar2 != 0) goto LAB_402061d1;
  iVar2 = FUN_40204254(puVar1,param_3);
  if (iVar2 == 0) {
    iVar2 = FUN_402042b0(puVar1);
    if (iVar2 == 0) goto LAB_402061d1;
    iStack_2c = iVar2;
    iVar3 = FUN_40205ac8(*puVar1,iVar2 + 4,param_3);
    iVar2 = iStack_2c;
    if (iVar3 == 0) goto LAB_402061d1;
  }
  *(undefined4 *)(iVar2 + 8) = 8;
  *(undefined4 *)(iVar2 + 0xc) = uStack_30;
LAB_402061d1:
  FUN_4021614c(param_2,PTR_DAT_40201938);
  FUN_40206154(puVar1,param_2);
  FUN_40216114(param_1,param_2);
  FUN_402024b0(local_40);
  return param_1;
}



/* ==== 40206200  FUN_40206200  size=141 ==== */

undefined4 FUN_40206200(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  uStack_30 = param_4;
  puVar1 = (undefined4 *)FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_402228a4(param_3);
  if (iVar2 != 0) goto LAB_40206261;
  iVar2 = FUN_40204254(puVar1,param_3);
  if (iVar2 == 0) {
    iVar2 = FUN_402042b0(puVar1);
    if (iVar2 == 0) goto LAB_40206261;
    iStack_2c = iVar2;
    iVar3 = FUN_40205ac8(*puVar1,iVar2 + 4,param_3);
    iVar2 = iStack_2c;
    if (iVar3 == 0) goto LAB_40206261;
  }
  *(undefined4 *)(iVar2 + 8) = 4;
  *(undefined4 *)(iVar2 + 0xc) = uStack_30;
LAB_40206261:
  FUN_4021614c(param_2,PTR_DAT_40201938);
  FUN_40206154(puVar1,param_2);
  FUN_40216114(param_1,param_2);
  FUN_402024b0(local_40);
  return param_1;
}



/* ==== 40206290  FUN_40206290  size=141 ==== */

undefined4 FUN_40206290(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  uStack_30 = param_4;
  puVar1 = (undefined4 *)FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_402228a4(param_3);
  if (iVar2 != 0) goto LAB_402062f1;
  iVar2 = FUN_40204254(puVar1,param_3);
  if (iVar2 == 0) {
    iVar2 = FUN_402042b0(puVar1);
    if (iVar2 == 0) goto LAB_402062f1;
    iStack_2c = iVar2;
    iVar3 = FUN_40205ac8(*puVar1,iVar2 + 4,param_3);
    iVar2 = iStack_2c;
    if (iVar3 == 0) goto LAB_402062f1;
  }
  *(undefined4 *)(iVar2 + 8) = 4;
  *(undefined4 *)(iVar2 + 0xc) = uStack_30;
LAB_402062f1:
  FUN_4021614c(param_2,PTR_DAT_40201938);
  FUN_40206154(puVar1,param_2);
  FUN_40216114(param_1,param_2);
  FUN_402024b0(local_40);
  return param_1;
}



/* ==== 4020633c  FUN_4020633c  size=220 ==== */

void FUN_4020633c(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [36];
  
  FUN_40216000(auStack_50,DAT_40206320);
  puVar2 = PTR_DAT_40201fcc;
  FUN_402023fc(PTR_DAT_40201fcc,auStack_50);
  uVar5 = FUN_40216fe4();
  puVar1 = PTR_DAT_40206324;
  *(undefined4 *)PTR_DAT_40206324 = uVar5;
  FUN_40215e1c(auStack_50);
  puVar3 = PTR_s_rc_save_code_3ffe8e78_4_40206328;
  FUN_40216000(auStack_44,PTR_s_rc_save_code_3ffe8e78_4_40206328);
  FUN_40206290(auStack_50,PTR_DAT_40201dd8,auStack_44,*(undefined4 *)puVar1);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  puVar4 = PTR_DAT_40206330;
  FUN_4021614c(PTR_DAT_40206330,PTR_DAT_4020632c);
  FUN_40216000(auStack_44,puVar3);
  FUN_40206290(auStack_50,puVar4,auStack_44,*(undefined4 *)puVar1);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  FUN_40216000(auStack_38,PTR_s_rcCode_json_40206334);
  FUN_40216114(auStack_44,puVar4);
  FUN_40201cdc(auStack_50,auStack_38,auStack_44);
  puVar1 = PTR_DAT_40201034;
  FUN_40214c0c(PTR_DAT_40201034,auStack_50);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  FUN_40215e1c(auStack_38);
  FUN_40214ba0(puVar1,PTR_DAT_40206338);
  FUN_40214c0c(puVar1,puVar4);
  FUN_402048f8(puVar2,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 40206418  FUN_40206418  size=149 ==== */

undefined4 FUN_40206418(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  int iStack_30;
  int iStack_2c;
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  iStack_30 = param_4;
  puVar1 = (undefined4 *)FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_402228a4(param_3);
  if (iVar2 != 0) goto LAB_40206481;
  iVar2 = FUN_40204254(puVar1,param_3);
  if (iVar2 == 0) {
    iVar2 = FUN_402042b0(puVar1);
    if (iVar2 == 0) goto LAB_40206481;
    iStack_2c = iVar2;
    iVar3 = FUN_40205ac8(*puVar1,iVar2 + 4,param_3);
    iVar2 = iStack_2c;
    if (iVar3 == 0) goto LAB_40206481;
  }
  uVar4 = 4;
  iVar3 = iStack_30;
  if (iStack_30 < 0) {
    iVar3 = -iStack_30;
    uVar4 = 5;
  }
  *(undefined4 *)(iVar2 + 8) = uVar4;
  *(int *)(iVar2 + 0xc) = iVar3;
LAB_40206481:
  FUN_4021614c(param_2,PTR_DAT_40201938);
  FUN_40206154(puVar1,param_2);
  FUN_40216114(param_1,param_2);
  FUN_402024b0(local_40);
  return param_1;
}



/* ==== 402064b0  FUN_402064b0  size=121 ==== */

void FUN_402064b0(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  byte bVar4;
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [20];
  
  puVar2 = PTR_s_maxSpeed_3ffe8c63_1_402058b0;
  FUN_40216000(auStack_30,PTR_s_maxSpeed_3ffe8c63_1_402058b0);
  puVar1 = PTR_DAT_40201fcc;
  FUN_402023fc(PTR_DAT_40201fcc,auStack_30);
  bVar4 = FUN_40216fe4();
  puVar3 = PTR_DAT_402058b4;
  if (100 < bVar4) {
    bVar4 = 100;
  }
  *PTR_DAT_402058b4 = bVar4;
  FUN_40215e1c(auStack_30);
  FUN_40216000(auStack_24,puVar2);
  FUN_40206418(auStack_30,PTR_DAT_40201dd8,auStack_24,*puVar3);
  FUN_40215e1c(auStack_30);
  FUN_40215e1c(auStack_24);
  FUN_40201ddc();
  FUN_402048f8(puVar1,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 40206530  FUN_40206530  size=94 ==== */

void FUN_40206530(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [32];
  
  FUN_40216000(auStack_34,PTR_s_timezone_4020596c);
  FUN_40216000(auStack_28,DAT_4020652c);
  puVar1 = PTR_DAT_40201fcc;
  FUN_402023fc(PTR_DAT_40201fcc,auStack_28);
  uVar2 = FUN_40216fe4();
  FUN_40206418(auStack_40,PTR_DAT_40201dd8,auStack_34,uVar2);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_28);
  FUN_40215e1c(auStack_34);
  FUN_40201ddc();
  FUN_402048f8(puVar1,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 40206590  FUN_40206590  size=161 ==== */

undefined4 FUN_40206590(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  uStack_30 = param_1;
  uStack_2c = param_4;
  puVar1 = (undefined4 *)FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_402228a4(param_3);
  if ((iVar2 == 0) &&
     ((iVar2 = FUN_40204254(puVar1,param_3), iVar2 != 0 ||
      ((iVar2 = FUN_402042b0(puVar1), iVar2 != 0 &&
       (iVar3 = FUN_40205ac8(*puVar1,iVar2 + 4,param_3), iVar3 != 0)))))) {
    iVar3 = FUN_402228a4(uStack_2c);
    if (iVar3 == 0) {
      iVar3 = FUN_40205a6c(uStack_2c,*puVar1);
      if (iVar3 == 0) goto LAB_40206605;
      *(undefined4 *)(iVar2 + 8) = 2;
    }
    else {
      *(undefined4 *)(iVar2 + 8) = 2;
      iVar3 = 0;
    }
    *(int *)(iVar2 + 0xc) = iVar3;
  }
LAB_40206605:
  FUN_4021614c(param_2,PTR_DAT_40201938);
  FUN_40206154(puVar1,param_2);
  FUN_40216114(uStack_30,param_2);
  FUN_402024b0(local_40);
  return uStack_30;
}



/* ==== 4020663c  FUN_4020663c  size=183 ==== */

void FUN_4020663c(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [12];
  
  puVar1 = PTR_s_ssidAP_40206634;
  FUN_40216000(auStack_28,PTR_s_ssidAP_40206634);
  FUN_40216000(auStack_40,puVar1);
  puVar2 = PTR_DAT_40201fcc;
  uVar4 = FUN_402023fc(PTR_DAT_40201fcc,auStack_40);
  FUN_40216114(auStack_34,uVar4);
  puVar1 = PTR_DAT_40201dd8;
  FUN_40206590(auStack_1c,PTR_DAT_40201dd8,auStack_28,auStack_34);
  FUN_40215e1c(auStack_1c);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_28);
  puVar3 = PTR_s_passwordAP_40206638;
  FUN_40216000(auStack_28,PTR_s_passwordAP_40206638);
  FUN_40216000(auStack_40,puVar3);
  uVar4 = FUN_402023fc(puVar2,auStack_40);
  FUN_40216114(auStack_34,uVar4);
  FUN_40206590(auStack_1c,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_1c);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_28);
  FUN_40201ddc();
  FUN_402048f8(puVar2,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 402066fc  FUN_402066fc  size=183 ==== */

void FUN_402066fc(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [12];
  
  puVar1 = PTR_s_ssid_3ffe8db2_1_402066f4;
  FUN_40216000(auStack_28,PTR_s_ssid_3ffe8db2_1_402066f4);
  FUN_40216000(auStack_40,puVar1);
  puVar2 = PTR_DAT_40201fcc;
  uVar4 = FUN_402023fc(PTR_DAT_40201fcc,auStack_40);
  FUN_40216114(auStack_34,uVar4);
  puVar1 = PTR_DAT_40201dd8;
  FUN_40206590(auStack_1c,PTR_DAT_40201dd8,auStack_28,auStack_34);
  FUN_40215e1c(auStack_1c);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_28);
  puVar3 = PTR_s_password_402066f8;
  FUN_40216000(auStack_28,PTR_s_password_402066f8);
  FUN_40216000(auStack_40,puVar3);
  uVar4 = FUN_402023fc(puVar2,auStack_40);
  FUN_40216114(auStack_34,uVar4);
  FUN_40206590(auStack_1c,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_1c);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_28);
  FUN_40201ddc();
  FUN_402048f8(puVar2,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  return;
}



/* ==== 40206818  http_routes_setup  size=435 ==== */

void http_routes_setup(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 auStack_40 [8];
  undefined *puStack_38;
  undefined *puStack_34;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [24];
  
  FUN_40216000(auStack_30,PTR_s_flashChip_402067b4);
  uVar2 = FUN_40212e10();
  FUN_40216260(auStack_20,uVar2,0x10);
  FUN_40206590(auStack_40,PTR_DAT_40201218,auStack_30,auStack_20);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_20);
  FUN_40215e1c(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__charts_json_402067b8);
  puVar1 = PTR_DAT_40201fcc;
  puStack_34 = PTR_FUN_402067bc;
  puStack_38 = PTR_LAB_402067c0;
  FUN_402021dc(PTR_DAT_40201fcc,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_DAT_402067c4);
  puStack_34 = PTR_FUN_402067c8;
  puStack_38 = PTR_LAB_402067cc;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__Off6_402067d0);
  puStack_34 = PTR_FUN_402067d4;
  puStack_38 = PTR_LAB_402067d8;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_DAT_402067dc);
  puStack_34 = PTR_FUN_402067e0;
  puStack_38 = PTR_LAB_402067e4;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__Off7_402067e8);
  puStack_34 = PTR_FUN_402067ec;
  puStack_38 = PTR_LAB_402067f0;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__config_live_json_402067f4);
  puStack_34 = PTR_LAB_402067f8;
  puStack_38 = PTR_LAB_402067fc;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__config_setup_json_40206800);
  puStack_34 = PTR_LAB_40206804;
  puStack_38 = PTR_LAB_40206808;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_402016cc(auStack_30,PTR_s__restart_4020680c);
  puStack_34 = PTR_FUN_40206810;
  puStack_38 = PTR_LAB_40206814;
  FUN_402021dc(puVar1,auStack_30,1,auStack_40);
  FUN_402226a4(auStack_40);
  FUN_40201070(auStack_30);
  FUN_4020c2c0(puVar1);
  *(undefined4 *)(puVar1 + 0x58) = 0;
  if (*(int *)(puVar1 + 0xa4) == 0) {
    FUN_40203080(puVar1);
  }
  FUN_4020c380(puVar1);
  return;
}



/* ==== 402069cc  FUN_402069cc  size=101 ==== */

void FUN_402069cc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [16];
  
  iVar1 = FUN_402015b8(param_3);
  if (iVar1 != 0) {
    FUN_40216000(auStack_1c,PTR_DAT_4020632c);
    FUN_40216114(auStack_34,param_1);
    FUN_40216114(auStack_40,param_2);
    FUN_40206590(auStack_28,auStack_1c,auStack_34,auStack_40);
    FUN_40215e1c(auStack_28);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(auStack_34);
    FUN_40211bb8(PTR_DAT_4020121c,auStack_1c);
    FUN_40215e1c(auStack_1c);
  }
  return;
}



/* ==== 40206a4c  FUN_40206a4c  size=313 ==== */

void FUN_40206a4c(void)

{
  undefined *puVar1;
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [32];
  
  puVar1 = PTR_DAT_40201dd8;
  FUN_4021614c(PTR_DAT_40201dd8,PTR_DAT_4020632c);
  FUN_40216000(auStack_28,PTR_s_SSDP_3ffe956f_6_40206a34);
  FUN_40216000(auStack_34,PTR_s_Kart_4__40206a38);
  FUN_40206590(auStack_40,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40216000(auStack_28,PTR_s_ssidAP_40206634);
  FUN_40216000(auStack_34,PTR_s_ktWiFi_40206a3c);
  FUN_40206590(auStack_40,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40216000(auStack_28,PTR_s_passwordAP_40206638);
  FUN_40216000(auStack_34,PTR_s_AP_PASSWORD_REDACTED_40206a40);
  FUN_40206590(auStack_40,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40216000(auStack_28,PTR_s_ssid_3ffe8db2_1_402066f4);
  FUN_40216000(auStack_34,PTR_s_CrazyDrift_40206a44);
  FUN_40206590(auStack_40,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40216000(auStack_28,PTR_s_password_402066f8);
  FUN_40216000(auStack_34,PTR_s_WIFI_PASSWORD_REDACTED_40206a48);
  FUN_40206590(auStack_40,puVar1,auStack_28,auStack_34);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40216000(auStack_34,PTR_s_timezone_4020596c);
  FUN_40206418(auStack_40,puVar1,auStack_34,4);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40216000(auStack_34,PTR_s_maxSpeed_3ffe8c63_1_402058b0);
  FUN_40206418(auStack_40,puVar1,auStack_34,0x3c);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  return;
}



/* ==== 40206b88  FUN_40206b88  size=157 ==== */

undefined4 * FUN_40206b88(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined *local_40 [2];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 auStack_30 [2];
  undefined4 uStack_28;
  undefined4 **ppuStack_24;
  undefined4 uStack_20;
  undefined4 *apuStack_1c [3];
  
  local_40[0] = PTR_PTR_40205738;
  uStack_38 = 0;
  uStack_34 = 0x100;
  uVar1 = FUN_40205708(local_40,param_2,10);
  iVar2 = FUN_40204254(uVar1,param_3);
  if (iVar2 == 0) {
    *param_1 = 0;
    param_1[2] = 0;
    goto LAB_40206c12;
  }
  if (*(int *)(iVar2 + 8) == 1) {
    if ((*(int *)(iVar2 + 0xc) == 0) ||
       (iVar3 = (*(code *)PTR_FUN_40204250)(PTR_DAT_40205b80), iVar3 != 0)) {
LAB_40206bd0:
      if (*(int *)(iVar2 + 0xc) != 0) {
        FUN_40216000(param_1);
        goto LAB_40206c12;
      }
    }
  }
  else if (*(int *)(iVar2 + 8) == 2) goto LAB_40206bd0;
  ppuStack_24 = apuStack_1c;
  auStack_30[0] = 0;
  uStack_28 = 0;
  uStack_20 = 0;
  apuStack_1c[0] = auStack_30;
  FUN_40205fe8(iVar2 + 8,&ppuStack_24);
  FUN_402160bc(param_1,auStack_30);
  FUN_40215e1c(auStack_30);
LAB_40206c12:
  FUN_402024b0(local_40);
  return param_1;
}



/* ==== 40206c40  FUN_40206c40  size=390 ==== */

void FUN_40206c40(void)

{
  undefined *puVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined1 auStack_80 [12];
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  undefined1 auStack_5c [12];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [20];
  uint uStack_30;
  
  FUN_40216000(auStack_44,PTR_DAT_40206c28);
  puVar1 = PTR_DAT_40201fcc;
  iVar5 = 0;
  uVar6 = *(uint *)(PTR_DAT_40201fcc + 0x8c);
  uStack_30 = uVar6 & 0xff;
  for (uVar4 = 0; (uVar4 & 0xff) < uStack_30; uVar4 = uVar4 + 1) {
    puVar3 = PTR_DAT_40201358;
    if ((int)uVar4 < *(int *)(puVar1 + 0x8c) + *(int *)(puVar1 + 0x94)) {
      puVar3 = (undefined *)(*(int *)(puVar1 + 0x90) + iVar5);
    }
    FUN_40216114(auStack_50,puVar3);
    puVar3 = PTR_DAT_40201358;
    if ((int)uVar4 < *(int *)(puVar1 + 0x8c) + *(int *)(puVar1 + 0x94)) {
      puVar3 = (undefined *)(*(int *)(puVar1 + 0x90) + iVar5 + 0xc);
    }
    FUN_40216114(auStack_5c,puVar3);
    puVar3 = PTR_DAT_40201358;
    if ((int)uVar4 < *(int *)(puVar1 + 0x8c) + *(int *)(puVar1 + 0x94)) {
      puVar3 = (undefined *)(*(int *)(puVar1 + 0x90) + iVar5 + 0xc);
    }
    FUN_40216114(auStack_80,puVar3);
    FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_80);
    FUN_40215e1c(auStack_80);
    iVar2 = FUN_402167d0(auStack_68,PTR_DAT_40201938);
    if (iVar2 == 0) {
      FUN_402166bc(auStack_80,PTR_s___3ffe8df0_0x11_40203ab8,auStack_50);
      FUN_4021646c(auStack_80,PTR_DAT_40206c2c);
      FUN_402160bc(auStack_74,auStack_80);
      FUN_402163d0(auStack_44,auStack_74);
      FUN_40215e1c(auStack_74);
      FUN_40215e1c(auStack_80);
      FUN_402163d0(auStack_44,auStack_68);
      FUN_4021614c(auStack_68,PTR_DAT_40201938);
    }
    FUN_4021646c(auStack_44,DAT_40204f00);
    if ((int)uVar4 < (int)((uVar6 & 0xff) - 1)) {
      FUN_4021646c(auStack_44,PTR_DAT_40206c30);
    }
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40215e1c(auStack_50);
    iVar5 = iVar5 + 0x18;
  }
  FUN_4021646c(auStack_44,PTR_DAT_40206c34);
  FUN_40216000(auStack_80,PTR_s_points_40206c38);
  FUN_40206418(auStack_74,auStack_44,auStack_80,10);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_refresh_40206c3c);
  FUN_40206418(auStack_74,auStack_44,auStack_80,1000);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40204c7c(puVar1,200,PTR_s_application_json_402022a8,auStack_44);
  FUN_40215e1c(auStack_44);
  return;
}



/* ==== 40206dd0  FUN_40206dd0  size=258 ==== */

void FUN_40206dd0(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 ***pppuVar5;
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [12];
  undefined4 ***local_2c [2];
  byte bStack_21;
  undefined1 auStack_20 [16];
  
  FUN_40216000(auStack_50,DAT_40206dc8);
  puVar2 = PTR_DAT_40201fcc;
  uVar4 = FUN_402023fc(PTR_DAT_40201fcc,auStack_50);
  FUN_40216114(auStack_20,uVar4);
  FUN_40215e1c(auStack_50);
  puVar3 = PTR_s_SSDP_3ffe956f_6_40206a34;
  FUN_40216000(auStack_44,PTR_s_SSDP_3ffe956f_6_40206a34);
  FUN_40216114(auStack_50,auStack_20);
  FUN_40206590(auStack_38,PTR_DAT_40201218,auStack_44,auStack_50);
  FUN_40215e1c(auStack_38);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  FUN_40216000(auStack_44,puVar3);
  FUN_40216114(auStack_50,auStack_20);
  puVar1 = PTR_DAT_40201dd8;
  FUN_40206590(auStack_38,PTR_DAT_40201dd8,auStack_44,auStack_50);
  FUN_40215e1c(auStack_38);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  FUN_40216000(auStack_44,puVar3);
  FUN_40206b88(auStack_38,puVar1,auStack_44);
  uVar4 = FUN_40212de8();
  FUN_40216260(auStack_50,uVar4,10);
  FUN_40216644(local_2c,auStack_38,auStack_50);
  pppuVar5 = local_2c;
  if ((bStack_21 & 0x80) != 0) {
    pppuVar5 = local_2c[0];
  }
  FUN_4020d604(PTR_DAT_40206dcc,pppuVar5);
  FUN_40215e1c(local_2c);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_38);
  FUN_40215e1c(auStack_44);
  FUN_40201ddc();
  FUN_402048f8(puVar2,200,PTR_s_text_plain_402022fc,PTR_s_OK_3ffe92ae_9_40205970);
  FUN_40215e1c(auStack_20);
  return;
}



/* ==== 40206edc  FUN_40206edc  size=301 ==== */

undefined4 FUN_40206edc(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 ***pppuVar3;
  undefined4 ***pppuVar4;
  undefined1 auStack_50 [12];
  undefined4 ***local_44 [2];
  byte bStack_39;
  undefined4 ***local_38 [2];
  byte bStack_2d;
  undefined1 auStack_2c [8];
  undefined1 auStack_24 [8];
  undefined1 auStack_1c [16];
  
  FUN_40213cbc(auStack_1c,0xc0,0xa8,100,1);
  FUN_40213cbc(auStack_24,0xc0,0xa8,100,1);
  FUN_40213cbc(auStack_2c,0xff,0xff,0xff,0);
  FUN_40216000(local_44,PTR_s_ip_3ffe8ceb_7_40206ed4);
  FUN_40213ce0(local_38,auStack_1c);
  FUN_40206590(auStack_50,PTR_DAT_40201218,local_44,local_38);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(local_38);
  FUN_40215e1c(local_44);
  puVar1 = PTR_DAT_40201a24;
  FUN_4020b430(PTR_DAT_40201a24,0);
  FUN_4020b130(puVar1,2);
  FUN_40213c34(local_38,auStack_1c);
  FUN_40213c34(local_44,auStack_24);
  FUN_40213c34(auStack_50,auStack_2c);
  FUN_4020ad30(puVar1,local_38,local_44,auStack_50);
  local_44[0] = (undefined4 ***)CONCAT22(local_44[0]._2_2_,0x35);
  FUN_40216000(auStack_50,PTR_DAT_40204600);
  FUN_4020f4c0(PTR_DAT_40206ed8,local_44,auStack_50,auStack_1c);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_ssidAP_40206634);
  puVar2 = PTR_DAT_40201dd8;
  FUN_40206b88(local_38,PTR_DAT_40201dd8,auStack_50);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_passwordAP_40206638);
  FUN_40206b88(local_44,puVar2,auStack_50);
  FUN_40215e1c(auStack_50);
  pppuVar3 = local_38;
  if ((bStack_2d & 0x80) != 0) {
    pppuVar3 = local_38[0];
  }
  pppuVar4 = local_44;
  if ((bStack_39 & 0x80) != 0) {
    pppuVar4 = local_44[0];
  }
  FUN_4020ae1c(puVar1,pppuVar3,pppuVar4,1,0,4);
  FUN_40215e1c(local_44);
  FUN_40215e1c(local_38);
  return 1;
}



/* ==== 4020700c  FUN_4020700c  size=33 ==== */

void FUN_4020700c(void)

{
  FUN_40206edc();
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 4020703c  FUN_4020703c  size=362 ==== */

void FUN_4020703c(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 ***pppuVar5;
  undefined4 ***pppuVar6;
  char cVar7;
  undefined1 auStack_70 [12];
  undefined1 auStack_64 [12];
  undefined1 auStack_58 [12];
  undefined4 ***local_4c [2];
  byte bStack_41;
  undefined4 ***local_40 [2];
  byte bStack_35;
  undefined1 auStack_34 [32];
  
  FUN_4020f520(PTR_DAT_40206ed8);
  puVar3 = PTR_DAT_40201a24;
  FUN_4020b020(PTR_DAT_40201a24,0);
  FUN_4020b130(puVar3,1);
  FUN_40216000(auStack_70,PTR_s_ssid_3ffe8db2_1_402066f4);
  puVar2 = PTR_DAT_40201dd8;
  FUN_40206b88(local_40,PTR_DAT_40201dd8,auStack_70);
  FUN_40215e1c(auStack_70);
  FUN_40216000(auStack_70,PTR_s_password_402066f8);
  FUN_40206b88(local_4c,puVar2,auStack_70);
  FUN_40215e1c(auStack_70);
  puVar2 = PTR_DAT_40201938;
  iVar4 = FUN_402167d0(local_40,PTR_DAT_40201938);
  if ((iVar4 == 0) || (iVar4 = FUN_402167d0(local_4c,puVar2), iVar4 == 0)) {
    pppuVar5 = local_40;
    if ((bStack_35 & 0x80) != 0) {
      pppuVar5 = local_40[0];
    }
    pppuVar6 = local_4c;
    if ((bStack_41 & 0x80) != 0) {
      pppuVar6 = local_4c[0];
    }
    FUN_4020b5a8(puVar3,pppuVar5,pppuVar6,0,0,1);
  }
  else {
    FUN_4020b558(puVar3);
  }
  puVar1 = PTR_DAT_40201034;
  cVar7 = '\v';
  while ((cVar7 = cVar7 + -1, cVar7 != '\0' && (iVar4 = FUN_4020b534(puVar3), iVar4 != 3))) {
    FUN_40214ba0(puVar1,PTR_DAT_40201a34);
    FUN_4021836c(1000);
  }
  iVar4 = FUN_4020b534(puVar3);
  if (iVar4 == 3) {
    FUN_40214c40(puVar1,puVar2);
    FUN_40214c40(puVar1,PTR_s_WiFi_connected_40207030);
    FUN_40214c40(puVar1,PTR_s_IP_address__40207034);
    FUN_4020b4a8(auStack_70,puVar3);
    FUN_40214c68(puVar1,auStack_70);
    FUN_40216000(auStack_64,PTR_s_ip_3ffe8ceb_7_40206ed4);
    FUN_4020b4a8(auStack_34,puVar3);
    FUN_40213ce0(auStack_58,auStack_34);
    FUN_40206590(auStack_70,PTR_DAT_40201218,auStack_64,auStack_58);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_58);
    FUN_40215e1c(auStack_64);
  }
  else {
    FUN_40214c40(puVar1,puVar2);
    FUN_40214c40(puVar1,PTR_s_WiFi_up_AP_40207038);
    FUN_40206edc();
  }
  FUN_40215e1c(local_4c);
  FUN_40215e1c(local_40);
  return;
}



/* ==== 402071b0  FUN_402071b0  size=33 ==== */

void FUN_402071b0(void)

{
  FUN_4020703c();
  FUN_402048f8(PTR_DAT_40201fcc,200,PTR_s_text_plain_402022fc,PTR_DAT_40201938);
  return;
}



/* ==== 40207204  wifi_setup  size=190 ==== */

void wifi_setup(void)

{
  undefined *puVar1;
  undefined1 auStack_30 [8];
  undefined *puStack_28;
  undefined *puStack_24;
  undefined1 auStack_20 [24];
  
  FUN_402016cc(auStack_20,PTR_s__ssid_402071d4);
  puVar1 = PTR_DAT_40201fcc;
  puStack_24 = PTR_FUN_402071d8;
  puStack_28 = PTR_LAB_402071dc;
  FUN_402021dc(PTR_DAT_40201fcc,auStack_20,1,auStack_30);
  FUN_402226a4(auStack_30);
  FUN_40201070(auStack_20);
  FUN_402016cc(auStack_20,PTR_s__ssidap_402071e0);
  puStack_24 = PTR_FUN_402071e4;
  puStack_28 = PTR_LAB_402071e8;
  FUN_402021dc(puVar1,auStack_20,1,auStack_30);
  FUN_402226a4(auStack_30);
  FUN_40201070(auStack_20);
  FUN_402016cc(auStack_20,PTR_s__wifion_402071ec);
  puStack_24 = PTR_FUN_402071f0;
  puStack_28 = PTR_LAB_402071f4;
  FUN_402021dc(puVar1,auStack_20,1,auStack_30);
  FUN_402226a4(auStack_30);
  FUN_40201070(auStack_20);
  FUN_402016cc(auStack_20,PTR_s__wifioff_402071f8);
  puStack_24 = PTR_FUN_402071fc;
  puStack_28 = PTR_LAB_40207200;
  FUN_402021dc(puVar1,auStack_20,1,auStack_30);
  FUN_402226a4(auStack_30);
  FUN_40201070(auStack_20);
  FUN_4020703c();
  return;
}



/* ==== 402072dc  FUN_402072dc  size=274 ==== */

void FUN_402072dc(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 auStack_a0 [12];
  undefined1 auStack_94 [12];
  undefined1 auStack_88 [12];
  undefined1 auStack_7c [12];
  undefined1 auStack_70 [12];
  undefined1 auStack_64 [12];
  undefined1 auStack_58 [12];
  undefined1 auStack_4c [12];
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [12];
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [20];
  
  FUN_40216000(auStack_1c,PTR_DAT_402072c4);
  puVar1 = PTR_DAT_40201218;
  FUN_40206b88(auStack_28,PTR_DAT_40201218,auStack_1c);
  uVar2 = FUN_402165e0(auStack_28,0,PTR_s___dIn____402072c8);
  FUN_402160bc(auStack_34,uVar2);
  FUN_4021646c(auStack_34,PTR_s____adcIn____402072cc);
  FUN_402160bc(auStack_40,auStack_34);
  FUN_40216000(auStack_4c,PTR_s_adcIn_402072d0);
  FUN_40206b88(auStack_58,puVar1,auStack_4c);
  FUN_40216644(auStack_64,auStack_40,auStack_58);
  FUN_4021646c(auStack_64,PTR_s____temperature1____402072d4);
  FUN_402160bc(auStack_70,auStack_64);
  FUN_40216000(auStack_7c,PTR_s_temperature1_402072d8);
  FUN_40206b88(auStack_88,puVar1,auStack_7c);
  FUN_40216644(auStack_94,auStack_70,auStack_88);
  FUN_4021646c(auStack_94,PTR_DAT_40201f24);
  FUN_402160bc(auStack_a0,auStack_94);
  FUN_40204c7c(PTR_DAT_40201fcc,200,PTR_s_text_json_40204f04,auStack_a0);
  FUN_40215e1c(auStack_a0);
  FUN_40215e1c(auStack_94);
  FUN_40215e1c(auStack_88);
  FUN_40215e1c(auStack_7c);
  FUN_40215e1c(auStack_70);
  FUN_40215e1c(auStack_64);
  FUN_40215e1c(auStack_58);
  FUN_40215e1c(auStack_4c);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_34);
  FUN_40215e1c(auStack_28);
  FUN_40215e1c(auStack_1c);
  return;
}



/* ==== 40207420  ssdp_setup  size=467 ==== */

void ssdp_setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 ***pppuVar6;
  undefined1 **ppuVar7;
  undefined1 *local_70 [2];
  undefined *puStack_68;
  undefined *puStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [12];
  undefined4 ***local_38 [2];
  byte bStack_2d;
  
  uVar5 = FUN_40212de8();
  FUN_40216260(auStack_50,uVar5,10);
  FUN_4021646c(auStack_50,PTR_DAT_402073f0);
  FUN_402160bc(auStack_60,auStack_50);
  uVar5 = FUN_40212e10();
  FUN_40216260(local_70,uVar5,10);
  FUN_40216644(local_38,auStack_60,local_70);
  FUN_40215e1c(local_70);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_50);
  FUN_402016cc(auStack_60,PTR_s__description_xml_402073f4);
  puVar2 = PTR_DAT_40201fcc;
  puStack_64 = PTR_FUN_402073f8;
  puStack_68 = PTR_LAB_402073fc;
  FUN_402021dc(PTR_DAT_40201fcc,auStack_60,1,local_70);
  FUN_402226a4(local_70);
  FUN_40201070(auStack_60);
  FUN_402016cc(auStack_60,PTR_s__ssdp_40207400);
  puStack_64 = PTR_FUN_40207404;
  puStack_68 = PTR_LAB_40207408;
  FUN_402021dc(puVar2,auStack_60,1,local_70);
  FUN_402226a4(local_70);
  FUN_40201070(auStack_60);
  puVar4 = PTR_DAT_40206dcc;
  FUN_4020d5e8(PTR_DAT_40206dcc,PTR_s_upnp_rootdevice_4020740c);
  FUN_4020d5d0(puVar4,PTR_s_description_xml_3ffe8e10_1_40207410);
  FUN_40222b08(puVar4,0x50);
  puVar3 = PTR_s_SSDP_3ffe956f_6_40206a34;
  FUN_40216000(auStack_44,PTR_s_SSDP_3ffe956f_6_40206a34);
  puVar2 = PTR_DAT_40201dd8;
  FUN_40206b88(auStack_50,PTR_DAT_40201dd8,auStack_44);
  uVar5 = FUN_40212de8();
  FUN_40216260(auStack_60,uVar5,10);
  FUN_40216644(local_70,auStack_50,auStack_60);
  ppuVar7 = local_70;
  if (((uint)puStack_68 & 0x80000000) != 0) {
    ppuVar7 = (undefined1 **)local_70[0];
  }
  FUN_4020d604(puVar4,ppuVar7);
  FUN_40215e1c(local_70);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  pppuVar6 = local_38;
  if ((bStack_2d & 0x80) != 0) {
    pppuVar6 = local_38[0];
  }
  FUN_4020d638(puVar4,pppuVar6);
  puVar1 = PTR_s___3ffe96af_0xe_40201cc8;
  FUN_4020d620(puVar4,PTR_s___3ffe96af_0xe_40201cc8);
  FUN_4020d654(puVar4,PTR_DAT_40207414);
  FUN_40216114(auStack_44,local_38);
  FUN_4021646c(auStack_44,puVar1);
  FUN_40216000(auStack_50,puVar3);
  FUN_40206b88(auStack_60,puVar2,auStack_50);
  FUN_40216644(local_70,auStack_44,auStack_60);
  ppuVar7 = local_70;
  if (((uint)puStack_68 & 0x80000000) != 0) {
    ppuVar7 = (undefined1 **)local_70[0];
  }
  FUN_4020d670(puVar4,ppuVar7);
  FUN_40215e1c(local_70);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  puVar2 = PTR_s_http___istu_ru_40207418;
  FUN_4020d68c(puVar4,PTR_s_http___istu_ru_40207418);
  FUN_4020d6a4(puVar4,PTR_s_IstuVt_4020741c);
  FUN_4020d6c0(puVar4,puVar2);
  FUN_4020d818(puVar4);
  FUN_40215e1c(local_38);
  return;
}



/* ==== 40207608  rc_setup  size=368 ==== */

void rc_setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined *local_50 [2];
  undefined *puStack_48;
  undefined *puStack_44;
  undefined1 auStack_40 [16];
  int iStack_30;
  
  uVar5 = rc_detect_noise_on_gpio(0xe);
  puVar3 = PTR_s_rc_swith_on___402075f4;
  puVar2 = PTR_DAT_40201804;
  puVar1 = PTR_DAT_40201034;
  *PTR_DAT_40201804 = uVar5;
  FUN_40214ba0(puVar1,puVar3);
  FUN_40214ddc(puVar1,*puVar2,10);
  if (*puVar2 != '\0') {
    FUN_40212cd0(PTR_DAT_40201808,0xe);
    FUN_402016cc(auStack_40,PTR_s__rcVal_402075f8);
    local_50[0] = PTR_FUN_402075fc;
    puStack_44 = PTR_FUN_40202ed0;
    puStack_48 = PTR_LAB_40202ed4;
    FUN_40202478(PTR_DAT_40201fcc,auStack_40,local_50);
    FUN_402226a4(local_50);
    FUN_40201070(auStack_40);
    FUN_40216000(local_50,PTR_s_rcCode_json_40206334);
    FUN_40201e24(auStack_40,local_50,0x1000);
    puVar4 = PTR_DAT_40206330;
    FUN_4021612c(PTR_DAT_40206330,auStack_40);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(local_50);
    puVar3 = PTR_s_rc_save_code_3ffe8e78_4_40206328;
    FUN_40216000(local_50,PTR_s_rc_save_code_3ffe8e78_4_40206328);
    uVar6 = json_read_int(puVar4,local_50);
    puVar2 = PTR_DAT_40206324;
    *(undefined4 *)PTR_DAT_40206324 = uVar6;
    FUN_40215e1c(local_50);
    FUN_40214ba0(puVar1,PTR_s_rc_save_code___40207600);
    FUN_40216000(local_50,puVar3);
    FUN_40206b88(auStack_40,puVar4,local_50);
    FUN_40214c0c(puVar1,auStack_40);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(local_50);
    FUN_40216000(local_50,puVar3);
    FUN_40206b88(auStack_40,puVar4,local_50);
    iStack_30 = FUN_402167d0(auStack_40,PTR_DAT_40201938);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(local_50);
    if (iStack_30 != 0) {
      FUN_40214c40(puVar1,PTR_s_NOT_rc_save_code_40207604);
      FUN_4021614c(puVar4,PTR_DAT_4020632c);
      *(undefined4 *)puVar2 = 1;
    }
    FUN_40216000(local_50,puVar3);
    FUN_40206290(auStack_40,puVar4,local_50,*(undefined4 *)puVar2);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(local_50);
    FUN_40216000(local_50,puVar3);
    FUN_40206290(auStack_40,PTR_DAT_40201218,local_50,*(undefined4 *)puVar2);
    FUN_40215e1c(auStack_40);
    FUN_40215e1c(local_50);
  }
  return;
}



/* ==== 40207778  FUN_40207778  size=376 ==== */

byte FUN_40207778(void)

{
  undefined *puVar1;
  undefined *puVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  undefined1 auStack_c0 [12];
  undefined1 auStack_b4 [12];
  undefined1 auStack_a8 [12];
  undefined1 auStack_9c [12];
  undefined1 auStack_90 [12];
  undefined1 auStack_84 [12];
  undefined1 auStack_78 [12];
  undefined1 auStack_6c [12];
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [12];
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [20];
  
  FUN_40216000(auStack_24,PTR_s_SSDP_3ffe956f_6_40206a34);
  puVar2 = PTR_DAT_40201dd8;
  FUN_40206b88(auStack_30,PTR_DAT_40201dd8,auStack_24);
  puVar1 = PTR_DAT_40201938;
  bVar3 = FUN_402167d0(auStack_30,PTR_DAT_40201938);
  FUN_40216000(auStack_3c,PTR_s_ssidAP_40206634);
  FUN_40206b88(auStack_48,puVar2,auStack_3c);
  bVar4 = FUN_402167d0(auStack_48,puVar1);
  FUN_40216000(auStack_54,PTR_s_passwordAP_40206638);
  FUN_40206b88(auStack_60,puVar2,auStack_54);
  bVar5 = FUN_402167d0(auStack_60,puVar1);
  FUN_40216000(auStack_6c,PTR_s_ssid_3ffe8db2_1_402066f4);
  FUN_40206b88(auStack_78,puVar2,auStack_6c);
  bVar6 = FUN_402167d0(auStack_78,puVar1);
  FUN_40216000(auStack_84,PTR_s_password_402066f8);
  FUN_40206b88(auStack_90,puVar2,auStack_84);
  bVar7 = FUN_402167d0(auStack_90,puVar1);
  FUN_40216000(auStack_9c,PTR_s_maxSpeed_3ffe8c63_1_402058b0);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  bVar8 = FUN_402167d0(auStack_a8,puVar1);
  FUN_40216000(auStack_b4,PTR_s_timezone_4020596c);
  FUN_40206b88(auStack_c0,puVar2,auStack_b4);
  bVar9 = FUN_402167d0(auStack_c0,puVar1);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_90);
  FUN_40215e1c(auStack_84);
  FUN_40215e1c(auStack_78);
  FUN_40215e1c(auStack_6c);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  FUN_40215e1c(auStack_48);
  FUN_40215e1c(auStack_3c);
  FUN_40215e1c(auStack_30);
  FUN_40215e1c(auStack_24);
  return bVar4 | bVar3 | bVar5 | bVar6 | bVar7 | bVar8 | bVar9;
}



/* ==== 402078f4  FUN_402078f4  size=151 ==== */

undefined4 * FUN_402078f4(undefined4 *param_1,undefined4 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_40 [2];
  undefined1 uStack_3e;
  undefined1 uStack_3d;
  uint uStack_30;
  uint uStack_2c;
  
  puVar1 = PTR_DAT_402078f0;
  *param_1 = 0;
  param_1[2] = 0;
  (*(code *)PTR_FUN_402014c0)(auStack_40,puVar1,5);
  uStack_30 = FUN_402226bc(param_2);
  uVar4 = 0;
  while (uVar4 < uStack_30) {
    uVar2 = FUN_40216a64(param_2,uVar4);
    uVar3 = uVar4 + 1;
    if (uVar2 == 0x25) {
      if (uVar4 + 2 < uStack_30) {
        uStack_2c = uVar4 + 2;
        uStack_3e = FUN_40216a64(param_2,uVar3);
        uStack_3d = FUN_40216a64(param_2,uStack_2c);
        uVar2 = FUN_402288a0(auStack_40,0,0x10);
        uVar3 = uVar4 + 3;
        uVar2 = uVar2 & 0xff;
      }
    }
    else if (uVar2 == 0x2b) {
      uVar2 = 0x20;
    }
    FUN_4021649c(param_1,uVar2);
    uVar4 = uVar3;
  }
  return param_1;
}



/* ==== 4020798c  FUN_4020798c  size=137 ==== */

void FUN_4020798c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int *param_5,undefined4 *param_6,undefined4 *param_7,int *param_8)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [20];
  undefined4 uStack_30;
  
  iVar2 = *param_8;
  iVar1 = *param_5;
  uStack_30 = param_2;
  FUN_40216c00(auStack_50,param_4,*param_6,*param_7);
  FUN_402078f4(auStack_44,auStack_50);
  FUN_4021612c(uStack_30,auStack_44);
  FUN_40215e1c(auStack_44);
  FUN_40215e1c(auStack_50);
  if ((iVar1 != -1) && ((iVar1 < iVar2 + -1 || (iVar2 == -1)))) {
    FUN_40216c00(auStack_50,param_4,iVar1 + 1,iVar2);
    FUN_402078f4(auStack_44,auStack_50);
    FUN_4021612c(param_3,auStack_44);
    FUN_40215e1c(auStack_44);
    FUN_40215e1c(auStack_50);
  }
  return;
}



/* ==== 40207bc0  FUN_40207bc0  size=176 ==== */

void FUN_40207bc0(int param_1)

{
  int iVar1;
  int *piVar2;
  
  FUN_4020c2c0();
  iVar1 = *(int *)(param_1 + 0xa8);
  if (iVar1 != 0) {
    iVar1 = *(int *)(iVar1 + -4) * 0x18 + iVar1;
    while (*(int *)(param_1 + 0xa8) != iVar1) {
      iVar1 = iVar1 + -0x18;
      FUN_4020305c(iVar1);
    }
    FUN_4022e938((int *)(iVar1 + -4),*(int *)(iVar1 + -4) * 0x18 + 4);
  }
  piVar2 = *(int **)(param_1 + 100);
  while (piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    piVar2 = (int *)piVar2[1];
    (**(code **)(iVar1 + 4))();
  }
  FUN_402226a4(param_1 + 0xf0);
  FUN_40215e1c(param_1 + 0xe4);
  FUN_40215e1c(param_1 + 0xd8);
  FUN_40215e1c(param_1 + 0xcc);
  FUN_40215e1c(param_1 + 0xbc);
  FUN_40215e1c(param_1 + 0xb0);
  if (*(int *)(param_1 + 0x98) != 0) {
    FUN_40201260();
  }
  FUN_402226a4(param_1 + 0x7c);
  FUN_402226a4(param_1 + 0x6c);
  FUN_40215e1c(param_1 + 0x48);
  FUN_4020bb54(param_1 + 0x24);
  return;
}



/* ==== 40207c74  FUN_40207c74  size=35 ==== */

void FUN_40207c74(void)

{
  undefined1 auStack_30 [44];
  
  FUN_4020bf7c(auStack_30,PTR_DAT_40205078);
  FUN_4020d504(PTR_DAT_40206dcc,auStack_30);
  FUN_4020bb54(auStack_30);
  return;
}



/* ==== 40207cdc  http_ota_update  size=449 ==== */

void http_ota_update(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined *puVar5;
  undefined4 ***pppuVar6;
  int unaff_a14;
  undefined1 auStack_70 [32];
  undefined4 ***apppuStack_50 [2];
  undefined *puStack_48;
  undefined *puStack_44;
  undefined *apuStack_40 [2];
  undefined *puStack_38;
  undefined *puStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  
  iStack_28 = param_2;
  FUN_4020bf5c(auStack_70);
  puVar1 = PTR_DAT_40201034;
  FUN_40214c40(PTR_DAT_40201034,PTR_s_Update_start_40207c98);
  FUN_40214c0c(puVar1,param_1);
  puVar5 = PTR_DAT_40207c9c;
  PTR_DAT_40207c9c[0x78] = 0;
  puStack_44 = PTR_FUN_40202ed0;
  apppuStack_50[0] = (undefined4 ***)PTR_LAB_40207ca0;
  *(undefined4 *)(puVar5 + 0x74) = 2;
  puStack_48 = PTR_LAB_40202ed4;
  uStack_2c = 2;
  FUN_40202ea0(PTR_DAT_40207ca4,apppuStack_50);
  FUN_402226a4(apppuStack_50);
  apppuStack_50[0] = (undefined4 ***)PTR_LAB_40207ca8;
  puStack_44 = PTR_FUN_40202ed0;
  puStack_48 = PTR_LAB_40202ed4;
  FUN_40202ea0(PTR_DAT_40207cac,apppuStack_50);
  FUN_402226a4(apppuStack_50);
  apuStack_40[0] = PTR_LAB_40207cb0;
  puStack_34 = PTR_LAB_40207cb4;
  puStack_38 = PTR_FUN_40207cb8;
  puStack_48 = (undefined *)0x0;
  uStack_30 = 0;
  FUN_402224cc(apppuStack_50,apuStack_40,uStack_2c);
  puStack_44 = puStack_34;
  puStack_48 = puStack_38;
  FUN_4022275c(apppuStack_50,PTR_DAT_40207cbc);
  uVar2 = *(undefined4 *)(puVar5 + 0x6c);
  *(undefined **)(puVar5 + 0x6c) = puStack_48;
  uVar3 = *(undefined4 *)(puVar5 + 0x70);
  *(undefined **)(puVar5 + 0x70) = puStack_44;
  puStack_48 = (undefined *)uVar2;
  puStack_44 = (undefined *)uVar3;
  FUN_402226a4(apppuStack_50);
  FUN_402226a4(apuStack_40);
  apuStack_40[0] = PTR_LAB_40207cc0;
  puStack_34 = PTR_FUN_40207cc4;
  puStack_38 = PTR_FUN_40207cc8;
  puStack_48 = (undefined *)uStack_30;
  FUN_402224f4(apppuStack_50,apuStack_40,uStack_2c);
  puStack_44 = puStack_34;
  puStack_48 = puStack_38;
  FUN_4022275c(apppuStack_50,PTR_DAT_40207ccc);
  uVar4 = *(uint *)(puVar5 + 0x5c);
  *(undefined **)(puVar5 + 0x5c) = puStack_48;
  uVar2 = *(undefined4 *)(puVar5 + 0x60);
  *(undefined **)(puVar5 + 0x60) = puStack_44;
  puStack_48 = (undefined *)uVar4;
  puStack_44 = (undefined *)uVar2;
  FUN_402226a4(apppuStack_50);
  FUN_402226a4(apuStack_40);
  if (iStack_28 == 1) {
    FUN_40216000(apppuStack_50,PTR_DAT_40201938);
    unaff_a14 = FUN_4020e218(puVar5,auStack_70,param_1,apppuStack_50);
LAB_40207e3a:
    FUN_40215e1c(apppuStack_50);
  }
  else if (iStack_28 == 0) {
    FUN_40216000(apppuStack_50,PTR_DAT_40201938);
    unaff_a14 = FUN_4020e268(puVar5,auStack_70,param_1,apppuStack_50);
    goto LAB_40207e3a;
  }
  if (unaff_a14 == 1) {
    puVar5 = PTR_s_HTTP_UPDATE_NO_UPDATES_40207cd4;
  }
  else {
    if (unaff_a14 != 2) {
      if (unaff_a14 == 0) {
        uVar2 = FUN_40222b30(puVar5);
        FUN_4020da54(apppuStack_50,puVar5);
        pppuVar6 = apppuStack_50;
        if (((uint)puStack_48 & 0x80000000) != 0) {
          pppuVar6 = apppuStack_50[0];
        }
        FUN_40214990(puVar1,PTR_s_HTTP_UPDATE_FAILD_Error___d____s_40207cd0,uVar2,pppuVar6);
        FUN_40215e1c(apppuStack_50);
      }
      goto LAB_40207e89;
    }
    puVar5 = PTR_s_HTTP_UPDATE_OK_40207cd8;
  }
  FUN_40214c40(puVar1,puVar5);
LAB_40207e89:
  FUN_4020bb54(auStack_70);
  return;
}



/* ==== 40207ea8  FUN_40207ea8  size=354 ==== */

void FUN_40207ea8(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 auStack_30 [32];
  
  if (*(int *)(param_1 + 0x58) == 0) {
    FUN_4020c448(auStack_30,param_1);
    iVar2 = FUN_40222984(auStack_30);
    if (iVar2 == 0) {
      FUN_4020bb54(auStack_30);
      return;
    }
    FUN_4020bfb0(param_1 + 0x24,auStack_30);
    *(undefined4 *)(param_1 + 0x58) = 1;
    uVar3 = (*(code *)PTR_FUN_40207ea4)();
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    FUN_4020bb54(auStack_30);
  }
  iVar4 = param_1 + 0x24;
  iVar2 = FUN_4020bbc8(iVar4);
  if ((iVar2 == 0) && (iVar2 = FUN_4020b92c(iVar4), iVar2 == 0)) goto LAB_40207fd4;
  iVar2 = FUN_4020b92c(iVar4);
  if ((iVar2 == 0) || (*(char *)(param_1 + 0xca) == '\0')) {
    if (*(int *)(param_1 + 0x58) != 1) {
      if (((*(int *)(param_1 + 0x58) == 2) && (iVar2 = FUN_40222a70(param_1), iVar2 == 0)) &&
         (iVar2 = (*(code *)PTR_FUN_40207ea4)(), (uint)(iVar2 - *(int *)(param_1 + 0x5c)) < 0x7d1))
      {
        iVar2 = FUN_4020b92c(iVar4);
        if (iVar2 != 0) {
          *(undefined4 *)(param_1 + 0x58) = 1;
        }
        goto LAB_40208000;
      }
      goto LAB_40207fd4;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = 1;
  }
  iVar2 = FUN_4020b92c(iVar4);
  if (iVar2 == 0) {
    iVar2 = (*(code *)PTR_FUN_40207ea4)();
    if ((uint)(iVar2 - *(int *)(param_1 + 0x5c)) < 0x1389) goto LAB_40208000;
    bVar1 = true;
  }
  else {
    iVar2 = FUN_40203ae0(param_1,iVar4);
    if (iVar2 == 1) {
LAB_40207f5e:
      iVar2 = FUN_4020bbc8(iVar4);
      if ((iVar2 != 0) || (iVar2 = FUN_4020b92c(iVar4), iVar2 != 0)) {
        *(undefined4 *)(param_1 + 0x58) = 2;
        uVar3 = (*(code *)PTR_FUN_40207ea4)();
        *(undefined4 *)(param_1 + 0x5c) = uVar3;
        return;
      }
    }
    else if (iVar2 == 2) {
      FUN_4020c1b8(iVar4,0);
    }
    else if (iVar2 == 0) {
      FUN_402235f0(iVar4,5000);
      *(undefined4 *)(param_1 + 0xac) = 0xfffffffe;
      FUN_40204df8(param_1);
      goto LAB_40207f5e;
    }
LAB_40207fd4:
    bVar1 = false;
  }
  FUN_4020bf5c(auStack_30);
  FUN_4020bfb0(iVar4,auStack_30);
  FUN_4020bb54(auStack_30);
  iVar2 = *(int *)(param_1 + 0x98);
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  if (iVar2 != 0) {
    FUN_40201260();
  }
  if (!bVar1) {
    return;
  }
LAB_40208000:
  FUN_402173a8();
  return;
}



/* ==== 40208014  main_loop  size=47 ==== */

void main_loop(void)

{
  FUN_4020fa98(PTR_DAT_402018f0);
  FUN_40207ea8(PTR_DAT_40201fcc);
  FUN_402173a8();
  FUN_402126b4(PTR_DAT_4020121c);
  FUN_40211594(PTR_DAT_40201b40);
  FUN_4020f87c(PTR_DAT_40206ed8);
  return;
}



/* ==== 40208044  dac_write  size=53 ==== */

void dac_write(undefined1 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_402058ac;
  FUN_40212ba0(PTR_DAT_402058ac,0x48);
  FUN_40212a48(puVar1,0x40);
  FUN_40212a48(puVar1,param_1);
  FUN_40212bf0(puVar1);
  return;
}



/* ==== 40208154  ride_tick_1s  size=3187 ==== */

void ride_tick_1s(void)

{
  ushort uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  char cVar7;
  byte bVar8;
  undefined2 uVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  undefined1 auStack_80 [12];
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  undefined1 auStack_5c [12];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [20];
  undefined *puStack_30;
  uint uStack_2c;
  
  FUN_40201940(auStack_44);
  FUN_402019a0(auStack_50);
  puVar4 = PTR_s_time_3ffe89d2_0xd_4020807c;
  FUN_40216000(auStack_80,PTR_s_time_3ffe89d2_0xd_4020807c);
  FUN_40216114(auStack_74,auStack_44);
  FUN_40216000(auStack_5c,puVar4);
  puVar2 = PTR_DAT_40201218;
  FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  puVar6 = PTR_s_date_3ffe92cb_2_40208080;
  FUN_40216000(auStack_80,PTR_s_date_3ffe92cb_2_40208080);
  FUN_40216114(auStack_74,auStack_50);
  FUN_40216000(auStack_5c,puVar6);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_74,puVar4);
  FUN_40216114(auStack_68,auStack_44);
  FUN_40206590(auStack_80,puVar2,auStack_74,auStack_68);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar6);
  FUN_40216114(auStack_68,auStack_50);
  FUN_40206590(auStack_80,puVar2,auStack_74,auStack_68);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_80,PTR_s_lengthDrive_40208084);
  FUN_40216290(auStack_74,*(undefined2 *)PTR_DAT_40208088,10);
  FUN_40216000(auStack_5c,PTR_s_lengthDrive_40208084);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_driveOn_4020808c);
  FUN_40216290(auStack_74,*PTR_DAT_40208090,10);
  FUN_40216000(auStack_5c,PTR_s_driveOn_4020808c);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_timeDriveOn_40208094);
  FUN_40216290(auStack_74,*PTR_DAT_40208098,10);
  FUN_40216000(auStack_5c,PTR_s_timeDriveOn_40208094);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_timeParking_4020809c);
  FUN_40216290(auStack_74,*PTR_DAT_402080a0,10);
  FUN_40216000(auStack_5c,PTR_s_timeParking_4020809c);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_remoteMode_402080a4);
  FUN_40216290(auStack_74,*PTR_DAT_402080a8,10);
  FUN_40216000(auStack_5c,PTR_s_remoteMode_402080a4);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_localModeStart_402080ac);
  FUN_40216290(auStack_74,*PTR_DAT_402080b0,10);
  FUN_40216000(auStack_5c,PTR_s_localModeStart_402080ac);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_localModeWaitStart_402080b4);
  FUN_40216290(auStack_74,*PTR_DAT_402080b8,10);
  FUN_40216000(auStack_5c,PTR_s_localModeWaitStart_402080b4);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_localModeDriveON_402080bc);
  FUN_40216290(auStack_74,*PTR_DAT_402080c0,10);
  FUN_40216000(auStack_5c,PTR_s_localModeDriveON_402080bc);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_MinDV_402080c4);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080c8,10);
  FUN_40216000(auStack_5c,PTR_s_MinDV_402080c4);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_s_MaxDV_402080cc);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080d0,10);
  FUN_40216000(auStack_5c,PTR_s_MaxDV_402080cc);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  puVar4 = PTR_DAT_402080d4;
  FUN_40216000(auStack_80,PTR_DAT_402080d4);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080d8,10);
  FUN_40216000(auStack_5c,puVar4);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_80,PTR_DAT_402080dc);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080e0,10);
  FUN_40216000(auStack_5c,PTR_DAT_402080dc);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  puVar6 = PTR_s_MinDDV_402080e4;
  FUN_40216000(auStack_80,PTR_s_MinDDV_402080e4);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080e8,10);
  FUN_40216000(auStack_5c,puVar6);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  puVar3 = PTR_s_MaxDDV_402080ec;
  FUN_40216000(auStack_80,PTR_s_MaxDDV_402080ec);
  FUN_40216260(auStack_74,*(undefined4 *)PTR_DAT_402080f0,10);
  FUN_40216000(auStack_5c,puVar3);
  FUN_40206b88(auStack_68,puVar2,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_74,PTR_s_lengthDrive_40208084);
  FUN_40206418(auStack_80,puVar2,auStack_74,*(undefined2 *)PTR_DAT_40208088);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_driveOn_4020808c);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_40208090);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_timeDriveOn_40208094);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_40208098);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_timeParking_4020809c);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_402080a0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_remoteMode_402080a4);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_402080a8);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_localModeStart_402080ac);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_402080b0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_localModeWaitStart_402080b4);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_402080b8);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_localModeDriveON_402080bc);
  FUN_40206418(auStack_80,puVar2,auStack_74,*PTR_DAT_402080c0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_MinDV_402080c4);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080c8);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_MaxDV_402080cc);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080d0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar4);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080d8);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_DAT_402080dc);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080e0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar6);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080e8);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_402080f0);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  if (*PTR_DAT_40208098 != '\0') {
    uVar1 = *(ushort *)PTR_DAT_40208088;
    iVar13 = *(int *)PTR_DAT_402080f4;
    iVar10 = time_now();
    puVar2 = PTR_s_LastDriveTime_402080fc;
    uVar12 = ((uint)uVar1 + iVar13) - iVar10;
    if (DAT_402080f8 < uVar12) {
      uVar12 = 0;
    }
    FUN_40216000(auStack_80,PTR_s_LastDriveTime_402080fc);
    FUN_40216234(auStack_74,uVar12,10);
    FUN_40216000(auStack_5c,puVar2);
    puVar4 = PTR_DAT_40201218;
    FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_5c);
    FUN_402069cc(auStack_80,auStack_74,auStack_68);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40215e1c(auStack_74);
    FUN_40215e1c(auStack_80);
    FUN_40216000(auStack_74,puVar2);
    FUN_40206200(auStack_80,puVar4,auStack_74,uVar12);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
  }
  if (*PTR_DAT_402080a0 != '\0') {
    iVar13 = *(int *)PTR_DAT_402080f4;
    iVar10 = time_now();
    puVar2 = PTR_s_LastParkingTime_40208100;
    uVar12 = (iVar13 + 0x3c) - iVar10;
    if (DAT_402080f8 < uVar12) {
      uVar12 = 0;
    }
    FUN_40216000(auStack_80,PTR_s_LastParkingTime_40208100);
    FUN_40216234(auStack_74,uVar12,10);
    FUN_40216000(auStack_5c,puVar2);
    puVar4 = PTR_DAT_40201218;
    FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_5c);
    FUN_402069cc(auStack_80,auStack_74,auStack_68);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40215e1c(auStack_74);
    FUN_40215e1c(auStack_80);
    FUN_40216000(auStack_74,puVar2);
    FUN_40206200(auStack_80,puVar4,auStack_74,uVar12);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
  }
  if ((*PTR_DAT_40208090 != '\0') && (*PTR_DAT_402080b8 == '\0')) {
    iVar13 = *(int *)PTR_DAT_402080f4;
    iVar10 = time_now();
    puVar2 = PTR_s_LastWaitTime_40208104;
    uVar12 = (iVar13 + 600) - iVar10;
    if (DAT_402080f8 < uVar12) {
      uVar12 = 0;
    }
    FUN_40216000(auStack_80,PTR_s_LastWaitTime_40208104);
    FUN_40216234(auStack_74,uVar12,10);
    FUN_40216000(auStack_5c,puVar2);
    puVar4 = PTR_DAT_40201218;
    FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_5c);
    FUN_402069cc(auStack_80,auStack_74,auStack_68);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_5c);
    FUN_40215e1c(auStack_74);
    FUN_40215e1c(auStack_80);
    FUN_40216000(auStack_74,puVar2);
    FUN_40206200(auStack_80,puVar4,auStack_74,uVar12);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
  }
  puVar2 = PTR_DAT_40208108;
  *(int *)PTR_DAT_40208108 = *(int *)PTR_DAT_40208108 + 1;
  gpio16_pulse_tick();
  if ((uint)(CONCAT44(*(int *)puVar2 * DAT_4020810c,*(int *)puVar2 * DAT_4020810c) >> 7) <=
      DAT_40208110) {
    FUN_40216000(auStack_80,PTR_s_timezone_4020596c);
    json_read_int(PTR_DAT_40201dd8,auStack_80);
    FUN_40201a3c();
    FUN_40215e1c(auStack_80);
  }
  puVar6 = PTR_s_uptime_40208114;
  FUN_40216000(auStack_80,PTR_s_uptime_40208114);
  FUN_40216260(auStack_74,*(undefined4 *)puVar2,10);
  FUN_40216000(auStack_5c,puVar6);
  puVar4 = PTR_DAT_40201218;
  FUN_40206b88(auStack_68,PTR_DAT_40201218,auStack_5c);
  FUN_402069cc(auStack_80,auStack_74,auStack_68);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_74,puVar6);
  FUN_40206290(auStack_80,puVar4,auStack_74,*(undefined4 *)puVar2);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  if (((byte)*PTR_DAT_40204a70 < 4) &&
     (cVar7 = *PTR_DAT_40204a70 + 1, *PTR_DAT_40204a70 = cVar7, cVar7 == '\x03')) {
    (*(code *)PTR_FUN_402018a0)(0x10,0);
  }
  cVar7 = *PTR_DAT_402080a8;
  iVar10 = (*(code *)PTR_FUN_40207ea4)();
  puVar2 = PTR_DAT_40201034;
  if ((DAT_4020811c < (uint)(iVar10 - *(int *)PTR_DAT_40208118)) && (cVar7 != '\x01')) {
    FUN_40214ba0(PTR_DAT_40201034,PTR_DAT_40208120);
    uVar11 = time_now();
    FUN_40216000(auStack_74,PTR_s_Time_reboot_40208124);
    puVar4 = PTR_DAT_40207a38;
    FUN_40206290(auStack_80,PTR_DAT_40207a38,auStack_74,uVar11);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
    FUN_40216000(auStack_74,PTR_s_TimeReboot_json_40208128);
    FUN_40216114(auStack_68,puVar4);
    FUN_40201cdc(auStack_80,auStack_74,auStack_68);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_68);
    FUN_40215e1c(auStack_74);
    FUN_40214c40(puVar2,PTR_s_Time__4020812c);
    FUN_40201940(auStack_80);
    FUN_40214c0c(puVar2,auStack_80);
    FUN_40215e1c(auStack_80);
    FUN_402019a0(auStack_80);
    FUN_40214c0c(puVar2,auStack_80);
    FUN_40215e1c(auStack_80);
    FUN_40212db8();
  }
  puVar6 = PTR_DAT_402080f4;
  puVar4 = PTR_DAT_402080a0;
  puVar2 = PTR_DAT_40208098;
  if ((*PTR_DAT_40208098 != '\0') &&
     (uVar1 = *(ushort *)PTR_DAT_40208088, iVar10 = *(int *)PTR_DAT_402080f4,
     uVar12 = time_now(), puVar3 = PTR_DAT_40201034, (uint)uVar1 + iVar10 < uVar12)) {
    FUN_40214ba0(PTR_DAT_40201034,PTR_DAT_40208130);
    puVar5 = PTR_DAT_402058b4;
    *puVar2 = 0;
    *puVar5 = 0x14;
    *puVar4 = 1;
    (*(code *)PTR_FUN_402018a0)(0xd,0);
    uVar11 = time_now();
    *(undefined4 *)puVar6 = uVar11;
    FUN_40214d50(puVar3,*PTR_DAT_402058b4,10);
  }
  puVar3 = PTR_DAT_402080b8;
  puVar6 = PTR_DAT_40208090;
  if (*PTR_DAT_402080b0 == '\0') {
LAB_40208c00:
    if (*PTR_DAT_402080b8 != '\0') {
LAB_40208b91:
      if (*PTR_DAT_402080a8 != '\0') {
        if (*puVar4 != '\0') goto LAB_40208c11;
        if (*puVar2 != '\0') goto LAB_40208d49;
        *PTR_DAT_40208138 = 1;
        dac_write(0);
        FUN_4021836c(100);
        FUN_40214c40(PTR_DAT_40201034,PTR_DAT_4020813c);
        *puVar3 = 0;
        *puVar6 = 0;
        (*(code *)PTR_FUN_402018a0)(0xc,0);
        (*(code *)PTR_FUN_402018a0)(0xd,0);
        raceslist_write_and_send();
        FUN_4021836c(900);
        *PTR_DAT_40208138 = 0;
      }
    }
    if (*puVar4 == '\0') goto LAB_40208d49;
  }
  else {
    if (*PTR_DAT_402080b8 != '\0') goto LAB_40208b91;
    if (*puVar4 == '\0') {
      if ((*puVar2 != '\0') || ((byte)*PTR_DAT_40208090 != 0)) goto LAB_40208d49;
      puStack_30 = PTR_DAT_40201034;
      uStack_2c = (uint)(byte)*PTR_DAT_40208090;
      FUN_40214ba0(PTR_DAT_40201034,PTR_DAT_40208134);
      FUN_40214d50(puStack_30,*PTR_DAT_402058b4,10);
      *PTR_DAT_402080b0 = (char)uStack_2c;
      puVar5 = PTR_DAT_40208088;
      uVar9 = 900;
      if (*PTR_DAT_40201804 == '\0') {
        uVar9 = 600;
      }
      *puVar3 = 1;
      *(undefined2 *)puVar5 = uVar9;
      *puVar6 = 1;
      (*(code *)PTR_FUN_402018a0)(0xd,1);
      goto LAB_40208c00;
    }
  }
LAB_40208c11:
  iVar10 = *(int *)PTR_DAT_402080f4;
  uVar12 = time_now();
  if (iVar10 + 0x3cU < uVar12) {
    *PTR_DAT_40208138 = 1;
    dac_write(0);
    FUN_4021836c(100);
    puVar2 = PTR_DAT_40201034;
    FUN_40214c40(PTR_DAT_40201034,PTR_DAT_40208140);
    *puVar4 = 0;
    (*(code *)PTR_FUN_402018a0)(0xc,0);
    (*(code *)PTR_FUN_402018a0)(0xd,0);
    FUN_4021836c(900);
    puVar4 = PTR_s_maxSpeed_3ffe8c63_1_402058b0;
    *PTR_DAT_40208138 = 0;
    FUN_40216000(auStack_80,puVar4);
    bVar8 = json_read_int(PTR_DAT_40201dd8,auStack_80);
    if (100 < bVar8) {
      bVar8 = 100;
    }
    *PTR_DAT_402058b4 = bVar8;
    FUN_40215e1c(auStack_80);
    if (*PTR_DAT_402080b8 != '\0') {
      *puVar6 = 1;
      (*(code *)PTR_FUN_402018a0)(0xd,1);
      FUN_40214c40(puVar2,PTR_DAT_40208144);
      uVar11 = time_now();
      puVar4 = PTR_DAT_40208148;
      puVar2 = PTR_s_raceslist_txt_40201f1c;
      *(undefined4 *)PTR_DAT_40208148 = uVar11;
      FUN_40216000(auStack_80,puVar2);
      FUN_40216234(auStack_68,*(undefined4 *)puVar4,10);
      FUN_4021646c(auStack_68,PTR_DAT_4020814c);
      FUN_402160bc(auStack_74,auStack_68);
      FUN_40201eb0(auStack_80,auStack_74);
      FUN_40215e1c(auStack_74);
      FUN_40215e1c(auStack_68);
      FUN_40215e1c(auStack_80);
    }
  }
LAB_40208d49:
  if (((*puVar6 != '\0') && (*PTR_DAT_402080b8 == '\0')) &&
     (iVar10 = *(int *)PTR_DAT_402080f4, uVar12 = time_now(), puVar2 = PTR_DAT_40208138,
     iVar10 + 600U < uVar12)) {
    *PTR_DAT_40208138 = 1;
    dac_write(0);
    FUN_4021836c(100);
    FUN_40214c40(PTR_DAT_40201034,PTR_DAT_40208150);
    *puVar6 = 0;
    (*(code *)PTR_FUN_402018a0)(0xc,0);
    (*(code *)PTR_FUN_402018a0)(0xd,0);
    FUN_4021836c(900);
    *puVar2 = 0;
  }
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  return;
}



/* ==== 40208dc8  ride_tick_1s_thunk  size=15 ==== */

void ride_tick_1s_thunk(void)

{
  ride_tick_1s();
  return;
}



/* ==== 40208e74  ws_event  size=1470 ==== */

void ws_event(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  byte bVar4;
  undefined2 uVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  int iVar8;
  undefined *puVar9;
  undefined1 auStack_70 [12];
  undefined1 auStack_64 [12];
  undefined1 auStack_58 [12];
  undefined1 auStack_4c [12];
  undefined1 auStack_40 [16];
  uint uStack_30;
  
  puVar1 = PTR_DAT_40201034;
  switch(param_1) {
  case 1:
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__Disconnected__40208ddc);
    puVar9 = PTR_DAT_402080b0;
    if (*PTR_DAT_402080a8 != '\0') {
      *PTR_DAT_402080a8 = 0;
      *puVar9 = 1;
      uVar7 = (*(code *)PTR_FUN_40207ea4)();
      *(undefined4 *)PTR_DAT_40208118 = uVar7;
    }
    FUN_40214990(puVar1,PTR_s_DriveON___d_40208de0,*PTR_DAT_40208090);
    FUN_40214990(puVar1,PTR_s_timeDriveOn___d_40208de4,*PTR_DAT_40208098);
    FUN_40214990(puVar1,PTR_s_timeParking___d_40208de8,*PTR_DAT_402080a0);
    FUN_40214990(puVar1,PTR_s_localModeStart___d_40208dec,*puVar9);
    FUN_40214990(puVar1,PTR_s_llocalModeWaitStart___d_40208df0,*PTR_DAT_402080b8);
    iVar8 = FUN_4020b534(PTR_DAT_40201a24);
    FUN_40214990(puVar1,PTR_s_WiFi_Connected___d_40208df4,iVar8 == 3);
    puVar9 = PTR_DAT_40201b2c;
    if ((byte)(*PTR_DAT_40208df8 + 1) < 5) {
      *PTR_DAT_40208df8 = *PTR_DAT_40208df8 + 1;
      return;
    }
    *PTR_DAT_40208df8 = 0;
    if ((byte)(*puVar9 + 1) < 2) {
      *puVar9 = *puVar9 + 1;
    }
    else {
      *puVar9 = 0;
    }
    puVar2 = PTR_DAT_40201b30;
    FUN_40216114(auStack_58,PTR_DAT_40201b30 + (uint)(byte)*puVar9 * 0xc);
    puVar3 = PTR_DAT_40201b38;
    uStack_30 = (uint)*(ushort *)(PTR_DAT_40201b34 + (uint)(byte)*puVar9 * 2);
    FUN_40216114(auStack_64,PTR_DAT_40201b38 + (uint)(byte)*puVar9 * 0xc);
    FUN_40216000(auStack_70,PTR_s_arduino_40201b3c);
    FUN_40210a44(PTR_DAT_40201b40,auStack_58,uStack_30,auStack_64,auStack_70);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_64);
    FUN_40215e1c(auStack_58);
    FUN_402166bc(auStack_40,PTR_s_WS_connect_to_40201b44,puVar2 + (uint)(byte)*puVar9 * 0xc);
    FUN_4021646c(auStack_40,PTR_s___3ffe9024_4_4020193c);
    FUN_402160bc(auStack_4c,auStack_40);
    FUN_40216290(auStack_58,*(undefined2 *)(PTR_DAT_40201b34 + (uint)(byte)*puVar9 * 2),10);
    FUN_40216644(auStack_64,auStack_4c,auStack_58);
    FUN_402163d0(auStack_64,puVar3 + (uint)(byte)*puVar9 * 0xc);
    FUN_402160bc(auStack_70,auStack_64);
    FUN_40214c0c(puVar1,auStack_70);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_64);
    FUN_40215e1c(auStack_58);
    FUN_40215e1c(auStack_4c);
    puVar6 = auStack_40;
    goto LAB_402090fb;
  case 2:
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__Connected_to_url___s_40208dfc,param_2);
    *PTR_DAT_40208df8 = 0;
    *PTR_DAT_402080a8 = 1;
    *PTR_DAT_402080b0 = 0;
    FUN_40216000(auStack_4c,PTR_DAT_4020632c);
    FUN_40216000(auStack_58,PTR_s_Command_40208e00);
    FUN_40216000(auStack_64,PTR_DAT_40208e04);
    FUN_40206590(auStack_70,auStack_4c,auStack_58,auStack_64);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_64);
    FUN_40215e1c(auStack_58);
    FUN_40216000(auStack_64,PTR_s_DUUID_40208e08);
    uVar7 = FUN_40212de8();
    FUN_40206418(auStack_70,auStack_4c,auStack_64,uVar7);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_64);
    FUN_40216000(auStack_64,DAT_40208e0c);
    uVar7 = time_now();
    FUN_40206200(auStack_70,auStack_4c,auStack_64,uVar7);
    FUN_40215e1c(auStack_70);
    FUN_40215e1c(auStack_64);
    FUN_40210b58(PTR_DAT_40201b40,auStack_4c);
    goto LAB_402090f8;
  case 3:
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__get_text___s_40208e10,param_2);
    FUN_40216000(auStack_4c,param_2);
    FUN_40214c0c(puVar1,auStack_4c);
    FUN_40216000(auStack_70,PTR_s_Command_40208e00);
    FUN_40206b88(auStack_58,auStack_4c,auStack_70);
    FUN_40215e1c(auStack_70);
    iVar8 = FUN_402167d0(auStack_58,DAT_40208e14);
    puVar1 = PTR_DAT_40201b40;
    if (iVar8 == 0) {
      iVar8 = FUN_402167d0(auStack_58,PTR_DAT_40208e30);
      puVar9 = PTR_DAT_40208138;
      if (iVar8 == 0) {
        iVar8 = FUN_402167d0(auStack_58,PTR_s_MaxSpeed_40208e38);
        if (iVar8 == 0) {
          iVar8 = FUN_402167d0(auStack_58,PTR_s_Status_40208e40);
          if (iVar8 == 0) {
            iVar8 = FUN_402167d0(auStack_58,PTR_s_Update_40208e48);
            if (iVar8 == 0) {
              iVar8 = FUN_402167d0(auStack_58,PTR_s_UpdateFS_40208e54);
              puVar9 = PTR_s_error_40208e58;
              if (iVar8 == 0) goto LAB_4020937e;
              FUN_40216000(auStack_64,PTR_s_file_url_40208e4c,iVar8);
              FUN_40206b88(auStack_70,auStack_4c,auStack_64);
              puVar9 = PTR_DAT_40207a34;
              FUN_4021612c(PTR_DAT_40207a34,auStack_70);
              FUN_40215e1c(auStack_70);
              FUN_40215e1c(auStack_64);
              FUN_40216114(auStack_70,puVar9);
              http_ota_update(auStack_70,1);
              FUN_40215e1c(auStack_70);
            }
            else {
              FUN_40216000(auStack_64,PTR_s_file_url_40208e4c);
              FUN_40206b88(auStack_70,auStack_4c,auStack_64);
              puVar9 = PTR_DAT_40207a34;
              FUN_4021612c(PTR_DAT_40207a34,auStack_70);
              FUN_40215e1c(auStack_70);
              FUN_40215e1c(auStack_64);
              FUN_40216114(auStack_70,puVar9);
              http_ota_update(auStack_70,0);
              FUN_40215e1c(auStack_70);
            }
            puVar9 = PTR_s_Update_OK_40208e50;
          }
          else {
            FUN_40210b58(puVar1,PTR_DAT_40201218);
            puVar9 = PTR_s_Status_OK_40208e44;
          }
        }
        else {
          FUN_40216000(auStack_70,PTR_s_Speed_3ffe92a5_3_40208e18);
          bVar4 = json_read_int(auStack_4c,auStack_70);
          if (100 < bVar4) {
            bVar4 = 100;
          }
          *PTR_DAT_402058b4 = bVar4;
          FUN_40215e1c(auStack_70);
          puVar9 = PTR_s_MaxSpeed_OK_40208e3c;
        }
      }
      else {
        *PTR_DAT_40208138 = 1;
        dac_write(0);
        FUN_4021836c(100);
        *PTR_DAT_40208090 = 0;
        *PTR_DAT_40208098 = 0;
        *PTR_DAT_402080a0 = 0;
        (*(code *)PTR_FUN_402018a0)(0xc,0);
        (*(code *)PTR_FUN_402018a0)(0xd,0);
        FUN_4021836c(900);
        puVar2 = PTR_s_maxSpeed_3ffe8c63_1_402058b0;
        *puVar9 = 0;
        FUN_40216000(auStack_70,puVar2);
        bVar4 = json_read_int(PTR_DAT_40201dd8,auStack_70);
        if (100 < bVar4) {
          bVar4 = 100;
        }
        *PTR_DAT_402058b4 = bVar4;
        FUN_40215e1c(auStack_70);
        puVar9 = PTR_s_Stop_OK_40208e34;
      }
    }
    else {
      (*(code *)PTR_FUN_402018a0)(0xd,1);
      *PTR_DAT_402080a0 = 0;
      FUN_40216000(auStack_70,PTR_s_Speed_3ffe92a5_3_40208e18);
      bVar4 = json_read_int(auStack_4c,auStack_70);
      if (100 < bVar4) {
        bVar4 = 100;
      }
      *PTR_DAT_402058b4 = bVar4;
      FUN_40215e1c(auStack_70);
      if (*PTR_DAT_40208098 == '\0') {
        FUN_40216000(auStack_70,PTR_s_Length_40208e1c);
        uVar5 = json_read_int(auStack_4c,auStack_70);
        *(undefined2 *)PTR_DAT_40208088 = uVar5;
        FUN_40215e1c(auStack_70);
        uVar7 = time_now();
        *(undefined4 *)PTR_DAT_402080f4 = uVar7;
        *PTR_DAT_40208090 = 1;
      }
      puVar9 = PTR_DAT_40208e24;
      if (*PTR_DAT_40208e20 != '\0') {
        *PTR_DAT_40208e20 = 0;
        *(undefined4 *)puVar9 = 0;
        FUN_40216000(auStack_64,PTR_s_localDrivesCount_40208e28);
        FUN_40206290(auStack_70,PTR_DAT_40201d44,auStack_64,*(undefined4 *)puVar9);
        FUN_40215e1c(auStack_70);
        FUN_40215e1c(auStack_64);
        save_localdrives_json();
      }
      puVar9 = PTR_s_Start_OK_40208e2c;
    }
LAB_4020937e:
    FUN_40210b48(puVar1,puVar9,0);
    FUN_40215e1c(auStack_58);
LAB_402090f8:
    puVar6 = auStack_4c;
LAB_402090fb:
    FUN_40215e1c(puVar6);
    break;
  case 4:
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__get_binary_length___u_40208e5c);
    (*(code *)PTR_FUN_40208e70)(param_2,param_3,0x10);
    break;
  case 9:
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__get_ping_40208e60);
    break;
  case 10:
    if ((uint)(ushort)(*(short *)PTR_DAT_40208e64 + 1U) == (DAT_40208e68 & 0xffff)) {
      *(undefined2 *)PTR_DAT_40208e64 = 0;
      FUN_40216000(auStack_70,PTR_s_timezone_4020596c);
      json_read_int(PTR_DAT_40201dd8,auStack_70);
      FUN_40201a3c();
      FUN_40215e1c(auStack_70);
    }
    else {
      *(ushort *)PTR_DAT_40208e64 = *(short *)PTR_DAT_40208e64 + 1U;
    }
    puVar1 = PTR_DAT_40201034;
    FUN_40214990(PTR_DAT_40201034,PTR_s__WSc__get_pong_40208e6c);
    FUN_40214990(puVar1,PTR_s_DriveON___d_40208de0,*PTR_DAT_40208090);
    FUN_40214990(puVar1,PTR_s_timeDriveOn___d_40208de4,*PTR_DAT_40208098);
    FUN_40214990(puVar1,PTR_s_timeParking___d_40208de8,*PTR_DAT_402080a0);
    FUN_40214990(puVar1,PTR_s_localModeStart___d_40208dec,*PTR_DAT_402080b0);
    FUN_40214990(puVar1,PTR_s_llocalModeWaitStart___d_40208df0,*PTR_DAT_402080b8);
    iVar8 = FUN_4020b534(PTR_DAT_40201a24);
    FUN_40214990(puVar1,PTR_s_WiFi_Connected___d_40208df4,iVar8 == 3);
  }
  return;
}



/* ==== 40209468  adc_read  size=78 ==== */

undefined1 adc_read(byte param_1)

{
  undefined *puVar1;
  undefined1 uVar2;
  
  puVar1 = PTR_DAT_402058ac;
  if (3 < param_1) {
    param_1 = 0;
  }
  FUN_40212ba0(PTR_DAT_402058ac,0x48);
  FUN_40212a48(puVar1,param_1 | 0x40);
  FUN_40212bf0(puVar1);
  FUN_40212b60(puVar1,0x48,2);
  FUN_4021298c(puVar1);
  uVar2 = FUN_4021298c(puVar1);
  return uVar2;
}



/* ==== 4020951c  sensors_tick_377ms  size=2929 ==== */

void sensors_tick_377ms(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  char cVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  undefined1 auStack_c0 [12];
  undefined1 auStack_b4 [12];
  undefined1 auStack_a8 [12];
  undefined1 auStack_9c [12];
  undefined1 auStack_90 [12];
  undefined1 auStack_84 [12];
  undefined1 auStack_78 [12];
  undefined1 auStack_6c [12];
  undefined1 auStack_60 [12];
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [12];
  undefined1 auStack_30 [28];
  
  uVar6 = (*(code *)PTR_FUN_40201784)(0xe);
  FUN_40216290(auStack_30,uVar6,10);
  uVar7 = FUN_40218404(0x11);
  FUN_40216290(auStack_b4,uVar7,10);
  FUN_4021649c(auStack_b4,0x5f);
  FUN_402160bc(auStack_c0,auStack_b4);
  uVar11 = (*(code *)PTR_FUN_40209514)(uVar7);
  iVar10 = 0;
  uVar11 = (*(code *)PTR_FUN_40209518)
                     ((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),DAT_402094b8,DAT_402094bc);
  uVar11 = (*(code *)PTR_FUN_40209518)
                     ((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),DAT_40205c00,DAT_402094c0);
  uVar6 = (undefined4)((ulonglong)uVar11 >> 0x20);
  FUN_40216184(auStack_a8,uVar6,(int)uVar11,uVar6,2);
  FUN_40216644(auStack_3c,auStack_c0,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  uVar6 = adc_read(2);
  FUN_402162d0(auStack_48,uVar6,10);
  iVar8 = adc_read(0);
  FUN_40216290(auStack_54,iVar8,10);
  uVar6 = adc_read(3);
  FUN_402162d0(auStack_60,uVar6,10);
  uVar6 = FUN_40212934(PTR_DAT_402094c4);
  FUN_402161bc(auStack_6c,uVar6,2);
  uVar6 = (*(code *)PTR_FUN_40201784)(0xc);
  FUN_40216290(auStack_78,uVar6,10);
  uVar6 = (*(code *)PTR_FUN_40201784)(0xd);
  FUN_40216290(auStack_84,uVar6,10);
  cVar5 = FUN_4020b7a0(PTR_DAT_40201a24);
  FUN_40216290(auStack_90,(int)cVar5,10);
  if (*PTR_DAT_40201804 != '\0') {
    iVar10 = FUN_40201814();
  }
  if ((0x55 < iVar8) && (*PTR_DAT_40208098 != '\0')) {
    *(int *)PTR_DAT_402094c8 = *(int *)PTR_DAT_402094c8 + -0x55 + iVar8;
  }
  iVar8 = (*(code *)PTR_FUN_40201784)(0xe);
  puVar2 = PTR_DAT_402080c8;
  if (iVar8 != 0) {
    if (*PTR_DAT_40208098 != '\0') {
      if (uVar7 < *(uint *)PTR_DAT_402080c8) {
        *(uint *)PTR_DAT_402080c8 = uVar7;
      }
      puVar1 = PTR_DAT_402080d0;
      if (*(uint *)PTR_DAT_402080d0 < uVar7) {
        *(uint *)PTR_DAT_402080d0 = uVar7;
      }
      uVar9 = *(int *)puVar1 - *(int *)puVar2;
      if (uVar9 < *(uint *)PTR_DAT_402080e8) {
        *(uint *)PTR_DAT_402080e8 = uVar9;
      }
      if (*(uint *)PTR_DAT_402080f0 < uVar9) {
        *(uint *)PTR_DAT_402080f0 = uVar9;
      }
    }
    if (uVar7 < *(uint *)PTR_DAT_402080d8) {
      *(uint *)PTR_DAT_402080d8 = uVar7;
    }
    if (*(uint *)PTR_DAT_402080e0 < uVar7) {
      *(uint *)PTR_DAT_402080e0 = uVar7;
    }
  }
  FUN_40216000(auStack_c0,PTR_DAT_402072c4);
  FUN_40216114(auStack_b4,auStack_30);
  FUN_40216000(auStack_9c,PTR_DAT_402072c4);
  puVar2 = PTR_DAT_40201218;
  FUN_40206b88(auStack_a8,PTR_DAT_40201218,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_DAT_402094cc);
  FUN_40216114(auStack_b4,auStack_3c);
  FUN_40216000(auStack_9c,PTR_DAT_402094cc);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_adcIn_402072d0);
  FUN_40216114(auStack_b4,auStack_48);
  FUN_40216000(auStack_9c,PTR_s_adcIn_402072d0);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  puVar1 = PTR_DAT_402094d0;
  FUN_40216000(auStack_c0,PTR_DAT_402094d0);
  FUN_40216114(auStack_b4,auStack_54);
  FUN_40216000(auStack_9c,puVar1);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_DAT_402094d4);
  FUN_40216114(auStack_b4,auStack_60);
  FUN_40216000(auStack_9c,PTR_DAT_402094d4);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_temperature1_402072d8);
  FUN_40216114(auStack_b4,auStack_6c);
  FUN_40216000(auStack_9c,PTR_s_temperature1_402072d8);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_Speed_3ffe92a5_3_40208e18);
  FUN_402162d0(auStack_b4,*PTR_DAT_402058b4,10);
  FUN_40216000(auStack_9c,PTR_s_Speed_3ffe92a5_3_40208e18);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_DAT_402094d8);
  FUN_40216114(auStack_b4,auStack_78);
  FUN_40216000(auStack_9c,PTR_DAT_402094d8);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_DAT_402094dc);
  FUN_40216114(auStack_b4,auStack_84);
  FUN_40216000(auStack_9c,PTR_DAT_402094dc);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_DAT_402094e0);
  FUN_40216114(auStack_b4,auStack_90);
  FUN_40216000(auStack_9c,PTR_DAT_402094e0);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_rc_coins_402094e4);
  FUN_40216260(auStack_b4,*(undefined4 *)PTR_DAT_4020189c,10);
  FUN_40216000(auStack_9c,PTR_s_rc_coins_402094e4);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_localDrivesCount_40208e28);
  puVar3 = PTR_DAT_40208e24;
  FUN_40216260(auStack_b4,*(undefined4 *)PTR_DAT_40208e24,10);
  FUN_40216000(auStack_9c,PTR_s_localDrivesCount_40208e28);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_blockLokalDrive_402094e8);
  FUN_40216290(auStack_b4,*PTR_DAT_40208e20,10);
  FUN_40216000(auStack_9c,PTR_s_blockLokalDrive_402094e8);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_c0,PTR_s_DrivePoints_402094ec);
  FUN_40216260(auStack_b4,*(undefined4 *)PTR_DAT_402094c8,10);
  FUN_40216000(auStack_9c,PTR_s_DrivePoints_402094ec);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_b4,PTR_DAT_402072c4);
  FUN_40216114(auStack_a8,auStack_30);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_DAT_402094cc);
  FUN_40216114(auStack_a8,auStack_3c);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_adcIn_402072d0);
  FUN_40216114(auStack_a8,auStack_48);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,puVar1);
  FUN_40216114(auStack_a8,auStack_54);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_DAT_402094d4);
  FUN_40216114(auStack_a8,auStack_60);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_temperature1_402072d8);
  FUN_40216114(auStack_a8,auStack_6c);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_Speed_3ffe92a5_3_40208e18);
  FUN_40206418(auStack_c0,puVar2,auStack_b4,*PTR_DAT_402058b4);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_DAT_402094d8);
  FUN_40216114(auStack_a8,auStack_78);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_DAT_402094dc);
  FUN_40216114(auStack_a8,auStack_84);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_DAT_402094e0);
  FUN_40216114(auStack_a8,auStack_90);
  FUN_40206590(auStack_c0,puVar2,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_rc_coins_402094e4);
  FUN_40206290(auStack_c0,puVar2,auStack_b4,*(undefined4 *)PTR_DAT_4020189c);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_localDrivesCount_40208e28);
  FUN_40206290(auStack_c0,puVar2,auStack_b4,*(undefined4 *)puVar3);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_blockLokalDrive_402094e8);
  FUN_40206418(auStack_c0,puVar2,auStack_b4,*PTR_DAT_40208e20);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  FUN_40216000(auStack_b4,PTR_s_DrivePoints_402094ec);
  FUN_40206290(auStack_c0,puVar2,auStack_b4,*(undefined4 *)PTR_DAT_402094c8);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  puVar1 = PTR_DAT_402080b8;
  puVar2 = PTR_DAT_40208090;
  if (*PTR_DAT_40201804 == '\0') {
    if ((((*PTR_DAT_40208090 != '\0') && (*PTR_DAT_40208e20 == '\0')) &&
        (iVar8 = (*(code *)PTR_FUN_40201784)(0xe), iVar8 != 0)) && (*PTR_DAT_402094f8 == '\0')) {
      (*(code *)PTR_FUN_402018a0)(0xc,1);
      (*(code *)PTR_FUN_402018a0)(0x10,1);
      puVar1 = PTR_DAT_40204a70;
      *puVar2 = 0;
      *puVar1 = 0;
      uVar6 = time_now();
      *(undefined4 *)PTR_DAT_402080f4 = uVar6;
      puVar1 = PTR_DAT_402094f8;
      *PTR_DAT_40208098 = 1;
      puVar2 = PTR_DAT_402080c8;
      *puVar1 = 1;
      *(undefined4 *)puVar2 = 0x400;
      puVar4 = PTR_DAT_402094fc;
      puVar1 = PTR_DAT_402094c8;
      puVar2 = PTR_DAT_40201034;
      *(undefined4 *)PTR_DAT_402080d0 = 0;
      *(undefined4 *)puVar1 = 0;
      FUN_40214ba0(puVar2,puVar4);
      FUN_40214d50(puVar2,*PTR_DAT_402058b4,10);
      if (*PTR_DAT_402080b8 != '\0') {
        FUN_40214c40(puVar2,PTR_DAT_40209500);
        puVar2 = PTR_s_localDrivesCount_40208e28;
        *(int *)puVar3 = *(int *)puVar3 + 1;
        FUN_40216000(auStack_b4,puVar2);
        FUN_40206290(auStack_c0,PTR_DAT_40201d44,auStack_b4,*(undefined4 *)puVar3);
        FUN_40215e1c(auStack_c0);
        FUN_40215e1c(auStack_b4);
        if (0x95 < *(uint *)puVar3) {
          *PTR_DAT_40208e20 = 1;
        }
        save_localdrives_json();
        uVar6 = time_now();
        puVar1 = PTR_DAT_40208148;
        puVar2 = PTR_s_raceslist_txt_40201f1c;
        *(undefined4 *)PTR_DAT_40208148 = uVar6;
        FUN_40216000(auStack_c0,puVar2);
        FUN_40216234(auStack_a8,*(undefined4 *)puVar1,10);
        FUN_4021646c(auStack_a8,PTR_DAT_40201998);
        FUN_402160bc(auStack_b4,auStack_a8);
        FUN_40201eb0(auStack_c0,auStack_b4);
        FUN_40215e1c(auStack_b4);
        FUN_40215e1c(auStack_a8);
        FUN_40215e1c(auStack_c0);
      }
    }
    iVar8 = (*(code *)PTR_FUN_40201784)(0xe);
    *PTR_DAT_402094f8 = iVar8 != 0;
    goto LAB_4020a046;
  }
  if (*PTR_DAT_402080b8 == '\0') {
    if (*PTR_DAT_40208090 != '\0') {
      uVar7 = (*(code *)PTR_FUN_40205c18)(*(undefined2 *)PTR_DAT_40208088,900);
      puVar1 = PTR_DAT_40201034;
      *(uint *)PTR_DAT_4020189c = uVar7 & 0xffff;
      FUN_40214ba0(puVar1,PTR_DAT_402094f0);
      FUN_40214d28(puVar1,*(undefined4 *)PTR_DAT_4020189c,10);
      FUN_40214ba0(puVar1,PTR_DAT_402094f4);
      FUN_40214ddc(puVar1,*(undefined2 *)PTR_DAT_40208088,10);
      (*(code *)PTR_FUN_402018a0)(0xc,1);
      *puVar2 = 0;
      uVar6 = time_now();
      *(undefined4 *)PTR_DAT_402080f4 = uVar6;
      *PTR_DAT_40208098 = 1;
      *PTR_DAT_402094f8 = 1;
      FUN_40214ba0(puVar1,PTR_DAT_402094fc);
      FUN_40214d50(puVar1,*PTR_DAT_402058b4,10);
    }
    if (iVar10 == 0) goto LAB_4020a046;
  }
  else {
    if (*PTR_DAT_40208090 == '\0') {
      if (iVar10 == 0) goto LAB_4020a046;
    }
    else {
      if (iVar10 == 0) goto LAB_4020a046;
      iVar8 = *(int *)PTR_DAT_40206324;
      if (((iVar10 == iVar8) || (iVar10 == iVar8 + -4)) ||
         ((iVar10 == iVar8 + -6 || (iVar10 == iVar8 + -7)))) {
        (*(code *)PTR_FUN_402018a0)(0xc,1);
        *(undefined4 *)PTR_DAT_4020189c = 1;
        *puVar2 = 0;
        uVar6 = time_now();
        puVar2 = PTR_DAT_40201034;
        *(undefined4 *)PTR_DAT_402080f4 = uVar6;
        puVar3 = PTR_DAT_402094fc;
        *PTR_DAT_40208098 = 1;
        *PTR_DAT_402094f8 = 1;
        FUN_40214ba0(puVar2,puVar3);
        FUN_40214d50(puVar2,*PTR_DAT_402058b4,10);
        if (*puVar1 != '\0') {
          FUN_40214c40(puVar2,PTR_DAT_40209500);
          uVar6 = time_now();
          puVar1 = PTR_DAT_40208148;
          puVar2 = PTR_s_raceslist_txt_40201f1c;
          *(undefined4 *)PTR_DAT_40208148 = uVar6;
          FUN_40216000(auStack_c0,puVar2);
          FUN_40216234(auStack_a8,*(undefined4 *)puVar1,10);
          FUN_4021646c(auStack_a8,PTR_DAT_40201998);
          FUN_402160bc(auStack_b4,auStack_a8);
          FUN_40201eb0(auStack_c0,auStack_b4);
          FUN_40215e1c(auStack_b4);
          FUN_40215e1c(auStack_a8);
          FUN_40215e1c(auStack_c0);
        }
        goto LAB_40209e40;
      }
    }
    iVar8 = *(int *)PTR_DAT_40206324;
    if (((iVar10 == iVar8) || (iVar10 == iVar8 + -4)) ||
       ((iVar10 == iVar8 + -6 || (iVar10 == iVar8 + -7)))) {
      *(int *)PTR_DAT_4020189c = *(int *)PTR_DAT_4020189c + 1;
    }
  }
LAB_40209e40:
  puVar2 = PTR_DAT_40201034;
  FUN_40214ba0(PTR_DAT_40201034,PTR_s______RCKey________40209504);
  FUN_40214d28(puVar2,iVar10,10);
  puVar3 = PTR_s_rc_val_4020950c;
  puVar1 = PTR_DAT_40209508;
  *(int *)PTR_DAT_40209508 = *(int *)PTR_DAT_40209508 + 1;
  FUN_40216000(auStack_c0,puVar3);
  FUN_40216260(auStack_b4,iVar10,10);
  FUN_40216000(auStack_9c,puVar3);
  puVar2 = PTR_DAT_40201218;
  FUN_40206b88(auStack_a8,PTR_DAT_40201218,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_b4,puVar3);
  FUN_40206290(auStack_c0,puVar2,auStack_b4,iVar10);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
  puVar3 = PTR_s_rc_counts_40209510;
  FUN_40216000(auStack_c0,PTR_s_rc_counts_40209510);
  FUN_40216260(auStack_b4,*(undefined4 *)puVar1,10);
  FUN_40216000(auStack_9c,puVar3);
  FUN_40206b88(auStack_a8,puVar2,auStack_9c);
  FUN_402069cc(auStack_c0,auStack_b4,auStack_a8);
  FUN_40215e1c(auStack_a8);
  FUN_40215e1c(auStack_9c);
  FUN_40215e1c(auStack_b4);
  FUN_40215e1c(auStack_c0);
  FUN_40216000(auStack_b4,puVar3);
  FUN_40206290(auStack_c0,puVar2,auStack_b4,*(undefined4 *)puVar1);
  FUN_40215e1c(auStack_c0);
  FUN_40215e1c(auStack_b4);
LAB_4020a046:
  FUN_40215e1c(auStack_90);
  FUN_40215e1c(auStack_84);
  FUN_40215e1c(auStack_78);
  FUN_40215e1c(auStack_6c);
  FUN_40215e1c(auStack_60);
  FUN_40215e1c(auStack_54);
  FUN_40215e1c(auStack_48);
  FUN_40215e1c(auStack_3c);
  FUN_40215e1c(auStack_30);
  return;
}



/* ==== 4020a098  sensors_tick_thunk  size=15 ==== */

void sensors_tick_thunk(void)

{
  sensors_tick_377ms();
  return;
}



/* ==== 4020a0a8  throttle_tick_30ms  size=99 ==== */

void throttle_tick_30ms(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = adc_read(2);
  iVar2 = (*(code *)PTR_FUN_40201784)(0xe);
  if (((iVar2 == 0) || (*PTR_DAT_40208138 != '\0')) ||
     (iVar2 = (*(code *)PTR_FUN_40201784)(0xc), iVar2 == 0)) {
    uVar1 = 0x2d;
  }
  else if (0x55 < uVar1) {
    iVar2 = (*(code *)PTR_FUN_40205e24)((uVar1 - 0x55) * (uint)(byte)*PTR_DAT_402058b4,100);
    uVar1 = iVar2 + 0x55U & 0xff;
  }
  dac_write(uVar1);
  return;
}



/* ==== 4020a144  sensors_setup  size=1465 ==== */

void sensors_setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  char cVar5;
  short sVar6;
  undefined4 uVar7;
  int iVar8;
  undefined *local_60 [2];
  undefined *puStack_58;
  undefined *puStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [32];
  
  FUN_40216000(auStack_50,PTR_s_DUUID_40208e08);
  uVar7 = FUN_40212de8();
  FUN_40216260(auStack_40,uVar7,10);
  puVar2 = PTR_DAT_40201218;
  FUN_40206590(local_60,PTR_DAT_40201218,auStack_50,auStack_40);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_40,PTR_s_Device_name_4020a10c);
  FUN_40216000(auStack_50,PTR_DAT_4020a110);
  FUN_40206590(local_60,puVar2,auStack_40,auStack_50);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_40);
  FUN_40216000(auStack_40,PTR_s_Device_model_4020a114);
  FUN_40216000(auStack_50,PTR_DAT_4020a118);
  FUN_40206590(local_60,puVar2,auStack_40,auStack_50);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_40);
  FUN_40216000(auStack_40,PTR_s_Firmvare_version_4020a11c);
  FUN_40216000(auStack_50,PTR_s_0_9_10_4020a120);
  FUN_40206590(local_60,puVar2,auStack_40,auStack_50);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_40);
  FUN_402016cc(auStack_50,PTR_s__Sensors_4020a124);
  local_60[0] = PTR_FUN_4020a128;
  puStack_54 = PTR_FUN_40202ed0;
  puStack_58 = PTR_LAB_40202ed4;
  FUN_40202478(PTR_DAT_40201fcc,auStack_50,local_60);
  FUN_402226a4(local_60);
  FUN_40201070(auStack_50);
  puVar3 = PTR_DAT_402094c4;
  FUN_4021294c(PTR_DAT_402094c4,2,0);
  FUN_40218498(0xe,0);
  FUN_40218498(0x11,0);
  FUN_40218498(0xc,1);
  (*(code *)PTR_FUN_402018a0)(0xc,0);
  FUN_40218498(0x10,1);
  (*(code *)PTR_FUN_402018a0)(0x10,0);
  FUN_40218498(0xd,1);
  (*(code *)PTR_FUN_402018a0)(0xd,0);
  FUN_4021836c(1000);
  puVar4 = PTR_DAT_4020a130;
  puVar1 = PTR_DAT_4020a12c;
  memw();
  if ((*PTR_DAT_4020a12c == '\0') && (iVar8 = FUN_40223668(PTR_DAT_4020a12c), iVar8 != 0)) {
    sVar6 = 1000;
    if (*(int *)(puVar3 + 0xc) != 1) {
      sVar6 = 2000;
    }
    *(short *)puVar4 = sVar6 + 500;
    FUN_40223688(puVar1);
  }
  FUN_40216000(auStack_50,PTR_s_dhttime_4020a134);
  FUN_40206418(local_60,puVar2,auStack_50,*(undefined2 *)puVar4);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40212934(puVar3);
  uVar7 = FUN_4021276c(puVar3);
  FUN_40216000(auStack_34,uVar7);
  puVar1 = PTR_DAT_40201034;
  FUN_40214ba0(PTR_DAT_40201034,PTR_s_Sen_ok___4020a138);
  FUN_40214c0c(puVar1,auStack_34);
  FUN_40216000(auStack_50,PTR_DAT_402072c4);
  uVar7 = (*(code *)PTR_FUN_40201784)(0xe);
  FUN_40206418(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094cc);
  uVar7 = FUN_40218404(0x11);
  FUN_40206418(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_adcIn_402072d0);
  uVar7 = adc_read(2);
  FUN_402162d0(auStack_40,uVar7,10);
  FUN_40206590(local_60,puVar2,auStack_50,auStack_40);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094d0);
  uVar7 = adc_read(0);
  FUN_402162d0(auStack_40,uVar7,10);
  FUN_40206590(local_60,puVar2,auStack_50,auStack_40);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094d4);
  uVar7 = adc_read(3);
  FUN_402162d0(auStack_40,uVar7,10);
  FUN_40206590(local_60,puVar2,auStack_50,auStack_40);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_temperature1_402072d8);
  uVar7 = FUN_40212934(puVar3);
  FUN_40206170(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_Speed_3ffe92a5_3_40208e18);
  FUN_402162d0(auStack_40,*PTR_DAT_402058b4,10);
  FUN_40206590(local_60,puVar2,auStack_50,auStack_40);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_40);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094d8);
  uVar7 = (*(code *)PTR_FUN_40201784)(0xc);
  FUN_40206418(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094dc);
  uVar7 = (*(code *)PTR_FUN_40201784)(0xd);
  FUN_40206418(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_DAT_402094e0);
  cVar5 = FUN_4020b7a0(PTR_DAT_40201a24);
  FUN_40206418(local_60,puVar2,auStack_50,(int)cVar5);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_rc_val_4020950c);
  uVar7 = FUN_40201814();
  FUN_40206290(local_60,puVar2,auStack_50,uVar7);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_rc_counts_40209510);
  FUN_40206290(local_60,puVar2,auStack_50,*(undefined4 *)PTR_DAT_40209508);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_rc_coins_402094e4);
  FUN_40206290(local_60,puVar2,auStack_50,*(undefined4 *)PTR_DAT_4020189c);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_lengthDrive_40208084);
  FUN_40206418(local_60,puVar2,auStack_50,*(undefined2 *)PTR_DAT_40208088);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_driveOn_4020808c);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_40208090);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_timeDriveOn_40208094);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_40208098);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_timeParking_4020809c);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_402080a0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_remoteMode_402080a4);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_402080a8);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_localModeStart_402080ac);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_402080b0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_localModeWaitStart_402080b4);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_402080b8);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_localModeDriveON_402080bc);
  FUN_40206418(local_60,puVar2,auStack_50,*PTR_DAT_402080c0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_LastDriveTime_402080fc);
  FUN_40206418(local_60,puVar2,auStack_50,0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_LastParkingTime_40208100);
  FUN_40206418(local_60,puVar2,auStack_50,0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  FUN_40216000(auStack_50,PTR_s_LastWaitTime_40208104);
  FUN_40206418(local_60,puVar2,auStack_50,0);
  FUN_40215e1c(local_60);
  FUN_40215e1c(auStack_50);
  puStack_54 = PTR_FUN_4020a13c;
  puStack_58 = PTR_LAB_4020a140;
  FUN_4020faf4(PTR_DAT_402018f0,0,0x179,local_60,0,1);
  FUN_402226a4(local_60);
  FUN_40215e1c(auStack_34);
  return;
}



/* ==== 4020a764  setup  size=1290 ==== */

void setup(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 extraout_a3;
  undefined4 extraout_a3_00;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [12];
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  undefined1 auStack_5c [12];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [20];
  undefined *puStack_30;
  
  puVar1 = PTR_DAT_40201034;
  FUN_40213b30(PTR_DAT_40201034,0x1c200,0x1c,0,1);
  FUN_4021836c(5);
  FUN_40214c40(puVar1,PTR_DAT_40201938);
  FUN_40214c40(puVar1,PTR_s_Start_FS_4020a700);
  FUN_40202f00();
  FUN_40216000(auStack_80,PTR_s_TimeReboot_json_40208128);
  FUN_40201e24(&local_90,auStack_80,0x1000);
  puVar2 = PTR_DAT_40207a38;
  FUN_4021612c(PTR_DAT_40207a38,&local_90);
  FUN_40215e1c(&local_90);
  FUN_40215e1c(auStack_80);
  puStack_30 = PTR_s_Time_reboot_40208124;
  FUN_40216000(&local_90,PTR_s_Time_reboot_40208124);
  uVar4 = FUN_40205740(puVar2,&local_90);
  FUN_40215e1c(&local_90);
  FUN_40214ba0(puVar1,PTR_s_timeReboot___4020a704);
  FUN_40216000(auStack_80,puStack_30);
  FUN_40206b88(&local_90,puVar2,auStack_80);
  FUN_40214c0c(puVar1,&local_90);
  FUN_40215e1c(&local_90);
  FUN_40215e1c(auStack_80);
  FUN_40216208(&local_90,extraout_a3,uVar4,0);
  iVar5 = FUN_402167d0(&local_90,PTR_DAT_4020a708);
  FUN_40215e1c(&local_90);
  if (iVar5 != 0) {
    FUN_40214c40(puVar1,PTR_s_Time_reboot_NUL_4020a70c);
    uVar4 = 10000;
  }
  uStack_88 = 0;
  uStack_84 = 0;
  uStack_8c = 0;
  local_90 = uVar4;
  FUN_40219880(&local_90,0);
  FUN_4022716c(PTR_DAT_4020a714,PTR_s_SAMT_4SAMST_M3_5_0_M10_5_0_3_4020a710,1);
  FUN_40228ad8();
  FUN_40214ba0(puVar1,PTR_s_Time_reboot___4020a718);
  FUN_40214f00(puVar1,extraout_a3_00,uVar4,0,10);
  FUN_40214c40(puVar1,PTR_s_Time__4020812c);
  FUN_40201940(auStack_80);
  FUN_40214c0c(puVar1,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_402019a0(auStack_80);
  FUN_40214c0c(puVar1,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40216000(auStack_74,PTR_s_Time_reboot_40208124);
  FUN_40201940(auStack_44);
  FUN_4021646c(auStack_44,PTR_DAT_40201998);
  FUN_402160bc(auStack_50,auStack_44);
  FUN_402019a0(auStack_5c);
  FUN_40216644(auStack_68,auStack_50,auStack_5c);
  FUN_40206590(auStack_80,PTR_DAT_40201218,auStack_74,auStack_68);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_50);
  FUN_40215e1c(auStack_44);
  FUN_40215e1c(auStack_74);
  FUN_40214c40(puVar1,PTR_s_Config_4020a71c);
  FUN_40216000(auStack_74,PTR_s_config_json_40201dd4);
  FUN_40201e24(auStack_80,auStack_74,0x1000);
  puVar2 = PTR_DAT_40201dd8;
  FUN_4021612c(PTR_DAT_40201dd8,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40214ba0(puVar1,PTR_s_Config___4020a720);
  FUN_40214c0c(puVar1,puVar2);
  iVar5 = FUN_40207778();
  if (iVar5 != 0) {
    FUN_40206a4c();
    FUN_40201ddc();
    FUN_40214ba0(puVar1,PTR_s_Default_config___4020a724);
    FUN_40214c0c(puVar1,puVar2);
  }
  puVar2 = PTR_s_SSDP_3ffe956f_6_40206a34;
  FUN_40216000(auStack_74,PTR_s_SSDP_3ffe956f_6_40206a34);
  FUN_40216000(auStack_5c,puVar2);
  FUN_40206b88(auStack_68,PTR_DAT_40201dd8,auStack_5c);
  FUN_40206590(auStack_80,PTR_DAT_40201218,auStack_74,auStack_68);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_68);
  FUN_40215e1c(auStack_5c);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,PTR_s_reboots_json_40201d90);
  FUN_40201e24(auStack_80,auStack_74,0x1000);
  puVar2 = PTR_DAT_40201d94;
  FUN_4021612c(PTR_DAT_40201d94,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  puVar3 = PTR_s_reboots_4020a728;
  FUN_40216000(auStack_80,PTR_s_reboots_4020a728);
  iVar5 = json_read_int(puVar2,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40214ba0(puVar1,PTR_s_reboots___4020a72c);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206b88(auStack_80,puVar2,auStack_74);
  FUN_40214c0c(puVar1,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206b88(auStack_80,puVar2,auStack_74);
  puStack_30 = (undefined *)FUN_402167d0(auStack_80,PTR_DAT_40201938);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  iVar5 = iVar5 + 1;
  if (puStack_30 != (undefined *)0x0) {
    FUN_40214c40(puVar1,PTR_s_reboots_NUL_4020a730);
    FUN_4021614c(puVar2,PTR_DAT_4020632c);
    iVar5 = 0;
  }
  FUN_40216000(auStack_74,puVar3);
  FUN_40206290(auStack_80,PTR_DAT_40201d94,auStack_74,iVar5);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206290(auStack_80,PTR_DAT_40201218,auStack_74,iVar5);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  save_reboots_json();
  FUN_40216000(auStack_74,PTR_s_localdrives_json_40201d40);
  FUN_40201e24(auStack_80,auStack_74,0x1000);
  puVar2 = PTR_DAT_40201d44;
  FUN_4021612c(PTR_DAT_40201d44,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  puVar3 = PTR_s_localDrivesCount_40208e28;
  FUN_40216000(auStack_80,PTR_s_localDrivesCount_40208e28);
  uVar4 = json_read_int(puVar2,auStack_80);
  *(undefined4 *)PTR_DAT_40208e24 = uVar4;
  FUN_40215e1c(auStack_80);
  FUN_40214ba0(puVar1,PTR_s_localDrivesCount___4020a734);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206b88(auStack_80,puVar2,auStack_74);
  FUN_40214c0c(puVar1,auStack_80);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40216000(auStack_74,puVar3);
  FUN_40206b88(auStack_80,puVar2,auStack_74);
  iVar5 = FUN_402167d0(auStack_80,PTR_DAT_40201938);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  if (iVar5 == 0) {
    if (0x95 < *(uint *)PTR_DAT_40208e24) {
      *PTR_DAT_40208e20 = 1;
    }
  }
  else {
    FUN_40214c40(puVar1,PTR_s_localDrivesCount_NUL_4020a738);
    FUN_4021614c(puVar2,PTR_DAT_4020632c);
    *(undefined4 *)PTR_DAT_40208e24 = 0;
    FUN_40216000(auStack_74,puVar3);
    FUN_40206290(auStack_80,puVar2,auStack_74,*(undefined4 *)PTR_DAT_40208e24);
    FUN_40215e1c(auStack_80);
    FUN_40215e1c(auStack_74);
    save_localdrives_json();
  }
  FUN_40216000(auStack_74,puVar3);
  FUN_40206290(auStack_80,PTR_DAT_40201218,auStack_74,*(undefined4 *)PTR_DAT_40208e24);
  FUN_40215e1c(auStack_80);
  FUN_40215e1c(auStack_74);
  FUN_40214c0c(puVar1,PTR_DAT_40201dd8);
  FUN_40214c40(puVar1,PTR_s_Start_WIFI_4020a73c);
  wifi_setup();
  FUN_40214c40(puVar1,PTR_s_Start_RC_4020a740);
  rc_setup();
  FUN_40214c40(puVar1,PTR_s_Start_sensors_4020a744);
  sensors_setup();
  FUN_40214c40(puVar1,PTR_s_Start_Time_4020a748);
  time_setup();
  FUN_40214c40(puVar1,PTR_s_Start_SSDP_4020a74c);
  ssdp_setup();
  FUN_40214c40(puVar1,PTR_s_Start_WebServer_4020a750);
  http_routes_setup();
  FUN_40214c40(puVar1,PTR_s_Start_WebSoketServer_4020a754);
  ws_server_setup();
  FUN_40214c40(puVar1,PTR_s_Start_Inter_4020a758);
  start_inter_1s_ticker();
  FUN_40214c40(puVar1,PTR_s_Start_ADC_DAC_4020a75c);
  adc_dac_setup();
  FUN_40214c40(puVar1,PTR_s_Start_WebSoketClient_4020a760);
  ws_client_begin();
  return;
}


