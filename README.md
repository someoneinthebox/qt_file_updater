# qt_file_updater
A simple plug-in module for Qt to check updates for your soft and for update as a result

# System requirements
If you want to encapsulate code in software source code - there is no Windows XP support and lower cause you can't rename files during this software running.

# Plug-in purpose
A plugin encapsulates into your Qt project and then you can check available update for your software by calling its controller. All you need is create protocol JSON-file with update data.

You no need to worry about intermediate versions if there is some files that not included in last. Update files map will get them all.

# How it works
1. A plugin checks your software updates by downloading update file with protocol data which example you can find below;
2. If there is some available update - you'll see description for each update in the label;
3. You can download available update - all files in each available version;
4. Plugin places downloaded files into sub-folder of application folder;
5. After that - you can install update - plugin replace files in application folder by files into sub-folder (plugin will make backup for replacing files);
6. After that - you can restart software.

# Quick start
Just include **.pri** file into your project and somewhere in your code call:

```c++
Controller_FU c(your_int_version_variable, "https://your_site.com/path_to_update_file");
c.exec();
```

# Protocol

### Example:

```json
{
    "programName": "Your_Software_Name",
    "actualVersion": "3.7.6.6",
    "versions":
    {
         "3766":
         {
              "desc": "Some update info",
              "updateFiles":
              {
                 "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
                 "test.ini": "https://cloud.your_site.com/index.php/s/K2Tbehgj7fs675fj/download"
              }
         },
         "3765":
         {
              "desc": "
              <p>3.7.6.5</p>
              <ul>
                <li>Description can be html-like.</li>
              </ul>
              ",
              "updateFiles":
              {
                 "need.dll": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
                 "test.sh": "https://cloud.your_site.com/index.php/s/K2Tbejhf88vsEVdJI/download"
              }
         },
         "3764":
         {
              "desc": "Another description",
              "updateFiles":
              {
                 "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download"
              }
         }
    }
}
```

### Description:


1. **programName** - string, software name;
2. **actualVersion** - string, your actual user-like software version;
3. **versions** - json object with data:
   - **N** - string, where N is software numeric version with data:
     - **desc** - string, update description;
     - **updateFiles** - json object with key - filename and value - url to file
