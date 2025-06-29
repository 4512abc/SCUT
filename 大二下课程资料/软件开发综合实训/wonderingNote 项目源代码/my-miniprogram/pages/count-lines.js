const fs = require('fs');
const path = require('path');

const targetExtensions = ['.js', '.json', '.wxml', '.wxss'];

let totalLines = 0;

function countLinesInFile(filePath) {
  try {
    const content = fs.readFileSync(filePath, 'utf8');
    const lines = content.split(/\r\n|\r|\n/).length;
    return lines;
  } catch (err) {
    console.error(`读取文件失败: ${filePath}`, err.message);
    return 0;
  }
}

function traverseDirectory(dirPath) {
  const entries = fs.readdirSync(dirPath, { withFileTypes: true });

  for (const entry of entries) {
    const fullPath = path.join(dirPath, entry.name);

    if (entry.isDirectory()) {
      traverseDirectory(fullPath);
    } else if (targetExtensions.includes(path.extname(entry.name))) {
      const lines = countLinesInFile(fullPath);
      totalLines += lines;
      console.log(`${fullPath} -> ${lines} 行`);
    }
  }
}

// 开始遍历当前目录
traverseDirectory(process.cwd());

console.log('-------------------------');
console.log(`总代码行数: ${totalLines}`);
