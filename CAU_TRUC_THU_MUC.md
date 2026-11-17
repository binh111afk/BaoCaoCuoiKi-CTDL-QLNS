# Cấu trúc thư mục

```text
HrApp/
│
├── main.cpp                           main()
│
├── Util.h / Util.cpp                  Util
├── Account.h / Account.cpp            Role, Account
├── Admin.h / Admin.cpp                Admin
├── Employee.h / Employee.cpp          Employee
├── UserProfile.h / UserProfile.cpp    ProfileField, UserProfile
├── AccountList.h                      AccountList<T>
├── Validator.h / Validator.cpp        Validator
├── HrSystem.h / HrSystem.cpp          HrSystem
├── Console.h / Console.cpp            Console
├── Menu.h / Menu.cpp                  Menu
├── AdminMenu.h / AdminMenu.cpp        AdminMenu
├── EmployeeMenu.h / EmployeeMenu.cpp  EmployeeMenu
├── Application.h / Application.cpp    Application
│
└── data/                              tự tạo khi chạy lần đầu
    ├── Administrators.txt             username matkhau
    ├── Employees.txt                  username matkhau co
    └── users/
        └── nva.txt                    4 dòng: họ tên, địa chỉ, số điện thoại, email
```

`AccountList` là lớp mẫu (template) nên được viết hết trong file `.h`.
