void Array_print(unsigned long *a, int i);
unsigned long mask_high16(unsigned long a);
unsigned long mask_low16(unsigned long b);
void Multiple64(unsigned long *x, unsigned long *y, unsigned long *z);
void Modulo64(unsigned long *z, unsigned long *z_mod);

void Array_print(unsigned long *a, int i) {
  for (i = i - 1; i >= 0; i--) {
    Serial.print(a[i], HEX); Serial.print(" ");
  }
  Serial.println();
}

unsigned long mask_high16(unsigned long a) {
  unsigned long a_mask;
  a_mask = (a & 0xffff0000) >> 0x00000010;

  return a_mask;
}

unsigned long mask_low16(unsigned long b) {
  unsigned long b_mask;
  b_mask = b & 0x0000ffff;

  return b_mask;
}


void Multiple64(unsigned long *x, unsigned long *y, unsigned long *z) {

  unsigned long tmp[4][4]; //各配列同士の乗算結果を格納
  unsigned long tmp_carry[4][4]; //tmpの桁上げ部分
  unsigned long ans[8], ans_carry[8]; //tmpの加算結果を格納、ansの桁上げ部分

  //乗算部分
  //*0
  tmp[0][3] = x[0] * y[0];
  tmp_carry[0][3] = mask_high16(tmp[0][3]);
  tmp[0][2] = x[1] * y[0];
  tmp_carry[0][2] = mask_high16(tmp[0][2]);
  tmp[0][1] = x[2] * y[0];
  tmp_carry[0][1] = mask_high16(tmp[0][1]);
  tmp[0][0] = x[3] * y[0];
  tmp_carry[0][0] = mask_high16(tmp[0][0]);

  //*1
  tmp[1][3] = x[0] * y[1];
  tmp_carry[1][3] = mask_high16(tmp[1][3]);
  tmp[1][2] = x[1] * y[1];
  tmp_carry[1][2] = mask_high16(tmp[1][2]);
  tmp[1][1] = x[2] * y[1];
  tmp_carry[1][1] = mask_high16(tmp[1][1]);
  tmp[1][0] = x[3] * y[1];
  tmp_carry[1][0] = mask_high16(tmp[1][0]);

  //*2
  tmp[2][3] = x[0] * y[2];
  tmp_carry[2][3] = mask_high16(tmp[2][3]);
  tmp[2][2] = x[1] * y[2];
  tmp_carry[2][2] = mask_high16(tmp[2][2]);
  tmp[2][1] = x[2] * y[2];
  tmp_carry[2][1] = mask_high16(tmp[2][1]);
  tmp[2][0] = x[3] * y[2];
  tmp_carry[2][0] = mask_high16(tmp[2][0]);

  //*3
  tmp[3][3] = x[0] * y[3];
  tmp_carry[3][3] = mask_high16(tmp[3][3]);
  tmp[3][2] = x[1] * y[3];
  tmp_carry[3][2] = mask_high16(tmp[3][2]);
  tmp[3][1] = x[2] * y[3];
  tmp_carry[3][1] = mask_high16(tmp[3][1]);
  tmp[3][0] = x[3] * y[3];
  tmp_carry[3][0] = mask_high16(tmp[3][0]);

  //加算部分
  ans[0] = mask_low16(tmp[0][3]);
  ans_carry[0] = mask_high16(ans[0]);
  ans[1] = mask_low16(tmp[0][2]) + mask_low16(tmp[1][3]) + tmp_carry[0][3] + ans_carry[0];
  ans_carry[1] = mask_high16(ans[1]);
  ans[2] = mask_low16(tmp[0][1]) + mask_low16(tmp[1][2]) + mask_low16(tmp[2][3]) + tmp_carry[0][2] + tmp_carry[1][3] + ans_carry[1];
  ans_carry[2] = mask_high16(ans[2]);
  ans[3] = mask_low16(tmp[0][0]) + mask_low16(tmp[1][1]) + mask_low16(tmp[2][2]) + mask_low16(tmp[3][3]) + tmp_carry[0][1] + tmp_carry[1][2] + tmp_carry[2][3] + ans_carry[2];
  ans_carry[3] = mask_high16(ans[3]);
  ans[4] = mask_low16(tmp[1][0]) + mask_low16(tmp[2][1]) + mask_low16(tmp[3][2]) + tmp_carry[0][0] + tmp_carry[1][1] + tmp_carry[2][2] + tmp_carry[3][3] + ans_carry[3];
  ans_carry[4] = mask_high16(ans[4]);
  ans[5] = mask_low16(tmp[2][0]) + mask_low16(tmp[3][1]) + tmp_carry[1][0] + tmp_carry[2][1] + tmp_carry[3][2] + ans_carry[4];
  ans_carry[5] = mask_high16(ans[5]);
  ans[6] = mask_low16(tmp[3][0]) + tmp_carry[2][0] + tmp_carry[3][1] + ans_carry[5];
  ans_carry[6] = mask_high16(ans[6]);
  ans[7] = tmp_carry[3][0] + ans_carry[6];
  ans_carry[7] = mask_high16(ans[7]);

  z[0] = mask_low16(ans[0]);
  z[1] = mask_low16(ans[1]);
  z[2] = mask_low16(ans[2]);
  z[3] = mask_low16(ans[3]);
  z[4] = mask_low16(ans[4]);
  z[5] = mask_low16(ans[5]);
  z[6] = mask_low16(ans[6]);
  z[7] = mask_low16(ans[7]);

}


void Modulo64(unsigned long *z, unsigned long *z_mod) {
  unsigned long tmp1[4]; //各配列の加算を格納
  unsigned long carry; //桁上げ部分
  unsigned long tmp2[4]; // tmp1 = 2^64 - 1のとき0にする

  //1回目の加算
  tmp1[0] = z[0] + z[4];
  carry = mask_high16(tmp1[0]);
  tmp1[1] = carry;
  tmp1[1] += z[1] + z [5];
  carry = mask_high16(tmp1[1]);
  tmp1[2] = carry;
  tmp1[2] += z[2] + z[6];
  carry = mask_high16(tmp1[2]);
  tmp1[3] = carry;
  tmp1[3] += z[3] + z[7];

  tmp2[0] = mask_low16(tmp1[0]);
  tmp2[1] = mask_low16(tmp1[1]);
  tmp2[2] = mask_low16(tmp1[2]);
  tmp2[3] = mask_low16(tmp1[3]);

  if (tmp2[3] == 0xffff && tmp2[2] == 0xffff && tmp2[1] == 0xffff && tmp2[0] == 0xffff) {
    tmp1[3] = 0;
    tmp1[2] = 0;
    tmp1[1] = 0;
    tmp1[0] = 0;
  }

  //2回目の加算
  carry = mask_high16(tmp1[3]);
  z_mod[0] = carry + mask_low16(tmp1[0]);
  carry = mask_high16(z_mod[0]);
  z_mod[1] = carry + mask_low16(tmp1[1]);
  carry = mask_high16(z_mod[1]);
  z_mod[2] = carry + mask_low16(tmp1[2]);
  carry = mask_high16(z_mod[2]);
  z_mod[3] = carry + mask_low16(tmp1[3]);

  z_mod[0] = mask_low16(z_mod[0]);
  z_mod[1] = mask_low16(z_mod[1]);
  z_mod[2] = mask_low16(z_mod[2]);
  z_mod[3] = mask_low16(z_mod[3]);

  if (z_mod[3] == 0xffff && z_mod[2] == 0xffff && z_mod[1] == 0xffff && z_mod[0] == 0xffff) {
    z_mod[3] = 0;
    z_mod[2] = 0;
    z_mod[1] = 0;
    z_mod[0] = 0;
  }

}
