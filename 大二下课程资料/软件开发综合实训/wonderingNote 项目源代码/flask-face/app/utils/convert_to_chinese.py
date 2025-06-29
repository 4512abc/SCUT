import json


def create_mapping(input_file, output_file):
    mapping = {}

    with open(input_file, 'r', encoding='utf-8') as f:
        for line in f:
            # 过滤空行
            if not line.strip():
                continue

            # 分割行内容
            parts = line.strip().split()

            try:
                # 提取英文标签（索引1）和中文标签（最后一个元素）
                en_label = parts[1]
                zh_label = parts[-1]
                mapping[en_label] = zh_label
            except IndexError:
                print(f"跳过格式异常的行: {line}")
                continue

    # 保存为JSON文件
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(mapping, f, ensure_ascii=False, indent=4)


if __name__ == "__main__":
    # 使用示例
    input_filename = "imagenet.txt"  # 你的原始文档文件名
    output_filename = "../service/chinese_labels.json"  # 输出的JSON文件名

    create_mapping(input_filename, output_filename)
    print(f"转换完成！结果已保存到 {output_filename}")