package com.example.administrator.jaja.net;

/**
 * Created by Administrator on 2016/3/18.
 * public static void arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
 * src:源数组； srcPos:源数组要复制的起始位置； dest:目的数组； destPos:目的数组放置的起始位置； length:复制的长度。
 */
public class NetDataCommand {
    private static final int CommandLen=2048;
    public byte []byteArrayData=new byte[CommandLen];
    private NetDataTypeTransform mDataTypeTransform=new NetDataTypeTransform();
    public NetDataCommand(){
    }
    public void setLoginData(int messageType,String Account,String Password) {
        // TODO Auto-generated constructor stub
        int AccountLength=Account.length();
        int PasswordLength = Password.length();
        byte[] messageTypeByte= mDataTypeTransform.IntToByteArray(messageType);//整形转换成byte类型
        System.arraycopy(messageTypeByte,0,byteArrayData,
                0,messageTypeByte.length);

        byte[] accountByte=mDataTypeTransform.StringToByteArray(Account + "\0");//字符串转换成类型
        System.arraycopy(accountByte,0,byteArrayData,
                messageTypeByte.length,accountByte.length);

        byte[] AccountLengthByte=mDataTypeTransform.IntToByteArray(AccountLength);
        System.arraycopy(AccountLengthByte,0,byteArrayData,
                messageTypeByte.length+messageTypeByte.length,AccountLengthByte.length);

        byte[] PasswordByte =mDataTypeTransform.StringToByteArray(Password + "\0");//字符串转换成类型
        System.arraycopy(PasswordByte,0,byteArrayData,
                messageTypeByte.length+AccountLengthByte.length+accountByte.length, PasswordByte.length);//

        byte[] PasswordLengthByte=mDataTypeTransform.IntToByteArray(PasswordLength);
        System.arraycopy(PasswordLengthByte,0,byteArrayData,
                messageTypeByte.length+AccountLengthByte.length+accountByte.length+PasswordLengthByte.length,PasswordLengthByte.length);

    }

    public byte[] getByteArrayData(){
        return byteArrayData;
    }
}
