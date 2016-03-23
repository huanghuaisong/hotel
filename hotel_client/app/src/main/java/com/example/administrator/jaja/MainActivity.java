package com.example.administrator.jaja;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import com.example.administrator.jaja.RecvThread.RegisterThread;
import com.example.administrator.jaja.RecvThread.loginThread;
import com.example.administrator.jaja.UserInterface.UserManagementInterface;
import com.example.administrator.jaja.UserInterface.UserRegisterInterface;

public class MainActivity extends Activity implements View.OnClickListener {
    private Button LoginButton;
    private Button RegisterButton;
    private EditText AccountEditText;
    private EditText PasswordEditText;
    private Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewByIdAndSetListener();
        initHandler();
    }

    public void findViewByIdAndSetListener(){
        AccountEditText=(EditText)findViewById(R.id.account);
        PasswordEditText=(EditText)findViewById(R.id.password);

        LoginButton=(Button)findViewById(R.id.login_button);
        LoginButton.setOnClickListener(this);

        RegisterButton=(Button)findViewById(R.id.register_user_button);
        RegisterButton.setOnClickListener(this);
    }

    public void initHandler(){
        mHandler = new Handler(){
            @Override
            public void handleMessage(Message msg){
                switch (msg.what){
                    case 0://messageType.LOGIN
                        Toast.makeText(getApplicationContext(),"登录成功",Toast.LENGTH_SHORT).show();
                        startUserManagementActivity();
                        break;
                    case 6://messageType.USER_REGISTER
                        Toast.makeText(getApplicationContext(),msg.arg1+"ok="+msg.obj,Toast.LENGTH_SHORT).show();
                        UserRegisterActivity();
                        break;
                }
            }
        };
    }


    public void startUserManagementActivity(){
        Intent startUserManagement=new Intent(this, UserManagementInterface.class);
        this.startActivity(startUserManagement);
    }

    public void UserRegisterActivity(){
        Intent UserRegister=new Intent(this, UserRegisterInterface.class);
        this.startActivity(UserRegister);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.login_button:
                doLogin();
            case R.id.register_user_button:
                doRegister();
                break;
        }
    }

    public void doLogin(){
        loginThread login=new loginThread(AccountEditText.getText().toString(),
                PasswordEditText.getText().toString(),messageType.LOGIN,mHandler);
        login.start();
    }

    public void doRegister(){
        RegisterThread registerThread=new RegisterThread(
                PasswordEditText.getText().toString(),messageType.USER_REGISTER,mHandler);
        registerThread.start();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
    }
}
