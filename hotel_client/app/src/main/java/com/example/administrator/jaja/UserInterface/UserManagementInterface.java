package com.example.administrator.jaja.UserInterface;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.widget.Button;

import com.example.administrator.jaja.R;

/**
 * Created by Administrator on 2016/3/15.
 */
public class UserManagementInterface extends Activity implements View.OnClickListener{
    private Button reservationButton;//入住
    private Button continueReservationButton;//续住
    private Button BookButton;//预订
    private Button ViewConsumptionButton;//查看消费情况
    private Button changePasswordButton;//修改密码

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.user_management_layout);
        findViewByIdAndSetListener();

    }
    public void findViewByIdAndSetListener(){
        reservationButton=(Button)findViewById(R.id.reservation_button);
        reservationButton.setOnClickListener(this);
        continueReservationButton=(Button)findViewById(R.id.continue_reservation_button);
        continueReservationButton.setOnClickListener(this);
        BookButton=(Button)findViewById(R.id.book_button);
        BookButton.setOnClickListener(this);
        ViewConsumptionButton=(Button)findViewById(R.id.view_consumption_button);
        ViewConsumptionButton.setOnClickListener(this);
        changePasswordButton=(Button)findViewById(R.id.change_password_button);
        changePasswordButton.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.reservation_button:
                break;
            case R.id.continue_reservation_button:
                break;
            case R.id.book_button:
                break;
            case R.id.view_consumption_button:
                break;
            case R.id.change_password_button:
                break;
        }
    }
    @Override
    protected void onResume(){
        super.onResume();

    }

   @Override
    public boolean onKeyDown(int keyCode,KeyEvent event){
       if(keyCode==KeyEvent.KEYCODE_BACK){
           // 创建退出对话框
           AlertDialog isExit = new AlertDialog.Builder(this).create();
           // 设置对话框标题
           isExit.setTitle("系统提示");
           // 设置对话框消息
           isExit.setMessage("确定要退出吗");
           // 添加选择按钮并注册监听
           isExit.setButton("确定", listener);
           isExit.setButton2("取消", listener);
           // 显示对话框
           isExit.show();
       }
       return false;
   }

    /**监听对话框里面的button点击事件*/
    DialogInterface.OnClickListener listener = new DialogInterface.OnClickListener()
    {
        public void onClick(DialogInterface dialog, int which)
        {
            switch (which)
            {
                case AlertDialog.BUTTON_POSITIVE:// "确认"按钮退出程序
                    finish();
                    break;
                case AlertDialog.BUTTON_NEGATIVE:// "取消"第二个按钮取消对话框
                    break;
                default:
                    break;
            }
        }
    };


}


